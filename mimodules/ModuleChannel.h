#pragma once
#include <string>
#include <stdint.h>
#include <new>
#include "ModuleBuffer.h"
#include "ModuleValue.h"

namespace mimodule
{
	enum class ModulChannelDirection
	{
		Input,
		Output
	};

	typedef struct ModuleChannelParameter_t
	{
		size_t Size;
		//Rest of structur driver depended
	}ModuleChannelParameter;

	class ModuleChannel
	{
	private:
		std::string _Id;
		ModuleByteSize _Size;
		ModuleBitOffset _BitOffset;
		ModulValueType _Type;
		ModuleValue _Value;
		ModuleValue _LastValue;
		ModulChannelDirection _Direction;
		ModuleChannelParameter* _Parameter;
		mimodule::ModuleValueChangedEvent* _Event;
		

	public:
		ModuleChannel() = default;
		ModuleChannel(const std::string& id, 
			const ModulValueType type, 
			const ModuleBitOffset bitOffset,
			const ModulChannelDirection direction,
			const ModuleChannelParameter* parameter = nullptr)
			:_Id(id)
			, _BitOffset(bitOffset)
			, _Type(type)
			, _Value(type,id)
			, _LastValue(type)
			, _Direction(direction)
			, _Event(nullptr)
			
		{
			if (parameter != nullptr)
			{
				_Parameter = (ModuleChannelParameter*) ::operator new(parameter->Size);
				memcpy(_Parameter, parameter, parameter->Size);
			}
		}

		ModuleChannel(const ModuleChannel& other)
			:_Id(other._Id)
			, _BitOffset(other._BitOffset)
			, _Type(other._Type)
			, _Value(other._Value)
			, _LastValue(other._LastValue)
			, _Direction(other._Direction)
			, _Parameter(other._Parameter) 
			, _Event(other._Event)
		{
			if (other._Parameter != nullptr)
			{
				_Parameter = (ModuleChannelParameter*) ::operator new(other._Parameter->Size);
				memcpy(_Parameter, other._Parameter, other._Parameter->Size);
			}
		}

		~ModuleChannel()
		{
			delete _Parameter;
		}

		bool registerChannelEvent(ModuleValueChangedEvent* valueChangedEvent,bool checkChanges)
		{
			if (valueChangedEvent != nullptr)
			{
				return _Value.registerChannelEvent(valueChangedEvent, checkChanges);
			}
			return false;
		}

		const std::string& id() const
		{
			return _Id;
		}

		const ModuleBitOffset bitOffset() const
		{
			return _BitOffset;
		}

		const ModulValueType type() const
		{
			return _Type;
		}

		const ModuleByteSize size() const
		{
			return _Size;
		}

		const ModulChannelDirection direction() const
		{
			return _Direction;
		}

		mimodule::ModuleValueChangedEvent* valueChangedEvent()
		{
			return _Event;
		}

		ModuleChannelParameter* parameter() const
		{
			return _Parameter;
		}

		void setValue(mimodule::ModuleBuffer& iobuffer)
		{
			switch (_Type)
			{
			case ModulValueType::Boolean:
			{
				bool val = iobuffer.getBoolean(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Double:
			{
				double val = iobuffer.getValue<double>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Float:
			{
				float val = iobuffer.getValue<float>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Int8:
			{
				int8_t val = iobuffer.getValue<int8_t>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Int16:
			{
				int16_t val = iobuffer.getValue<int16_t>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Int32:
			{
				int32_t val = iobuffer.getValue<int32_t>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Int64:
			{
				int32_t val = iobuffer.getValue<int32_t>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Uint8:
			{
				uint8_t val = iobuffer.getValue<uint8_t>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Uint16:
			{
				uint16_t val = iobuffer.getValue<uint16_t>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Uint32:
			{
				uint32_t val = iobuffer.getValue<uint32_t>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			case ModulValueType::Uint64:
			{
				uint64_t val = iobuffer.getValue<uint64_t>(_BitOffset);
				_Value.setValue(val);
				break;
			}
			
			}
			
		}

		ModuleValue& value()
		{
			return _Value;
		}
	};
}