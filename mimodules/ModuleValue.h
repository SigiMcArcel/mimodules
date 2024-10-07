#pragma once

#include <string>
#include <stdint.h>
#include <memory>
#include "ModuleInterface.h"

namespace mimodule
{
	enum class ModulValueType
	{
		Boolean,
		Uint8,
		Uint16,
		Uint32,
		Uint64,
		Int8,
		Int16,
		Int32,
		Int64,
		Float,
		Double
	};

	class ModuleValue
	{
		typedef std::shared_ptr<uint8_t[]> BufferData;
	private:
		BufferData  _Buffer;
		ModulValueType _Type;
		mimodule::ModuleValueChangedEvent* _Event;
		std::string _ChannelName;
		bool _CheckChanges;

	public:
		ModuleValueChangedEvent* getEvent()
		{
			return _Event;
		}

		std::string& getChannelName()
		{
			return _ChannelName;
		}

		ModulValueType getType()
		{
			return _Type;
		}

		bool registerChannelEvent(ModuleValueChangedEvent* valueChangedEvent, bool checkChanges)
		{
			_CheckChanges = checkChanges;
			if (valueChangedEvent != nullptr)
			{
				_Event = valueChangedEvent;
				return true;
			}
			return false;
		}

		int32_t getSizeFromType(ModulValueType type)
		{
			switch (type)
			{
			case ModulValueType::Boolean:
			case ModulValueType::Int8:
			case ModulValueType::Uint8:
			{
				return 1;
			}
			case ModulValueType::Int16:
			case ModulValueType::Uint16:
			{
				return 2;
			}
			case ModulValueType::Float:
			case ModulValueType::Int32:
			case ModulValueType::Uint32:
			{
				return 4;
			}
			case ModulValueType::Int64:
			case ModulValueType::Uint64:
			case ModulValueType::Double:
			{
				return 8;
			}
			}
			return -1;
		}

		ModuleValue()
			:_Buffer()
			, _Type(ModulValueType::Boolean)
			, _Event(nullptr)
			, _ChannelName("")
			, _CheckChanges(false)
		{

		}

		ModuleValue(ModulValueType type)
			: _Buffer(new uint8_t[getSizeFromType(type)], std::default_delete<uint8_t[]>())
			, _Type(type)
			, _Event(nullptr)
			, _ChannelName("")
			, _CheckChanges(false)
		{

		}

		ModuleValue(ModulValueType type,const std::string& channelName)
			:_Buffer(new uint8_t[getSizeFromType(type)], std::default_delete<uint8_t[]>())
			, _Type(type)
			, _Event(nullptr)
			, _ChannelName(channelName)
			, _CheckChanges(false)
		{
			
		}

		ModuleValue(const ModuleValue& other)
			: _Buffer(other._Buffer)
			, _Type(other._Type)
			, _Event(other._Event)
			, _ChannelName(other._ChannelName)
			, _CheckChanges(other._CheckChanges)

		{
			
		}

		template<typename T>
		void setValue(T& value,bool forceEvent = false)
		{
			T lastValue = *reinterpret_cast<T*>(_Buffer.get());
			*reinterpret_cast<T*>(_Buffer.get()) = value;
			if (_CheckChanges && !forceEvent)
			{
				if (lastValue != value)
				{
					if (_Event != nullptr)
					{
						_Event->ValueChanged(*this, _ChannelName);
					}
				}
			}
			else
			{
				if (_Event != nullptr)
				{
					_Event->ValueChanged(*this, _ChannelName);
				}
			}
		}

		template<typename T>
		T getValue()
		{
			T value = *reinterpret_cast<T*>(_Buffer.get()); 
			return value;
		}
	};
}

