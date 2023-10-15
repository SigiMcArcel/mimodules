#pragma once
#include <string>
#include <stdint.h>
#include "ModuleInterface.h"
#include "ModuleBuffer.h"
#include "ModuleValue.h"

namespace mimodule
{
	enum class ModulChannelDirection
	{
		Input,
		Output
	};
	
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
		mimodule::ModuleValueChangedEvent* _Event;
		

	public:
		ModuleChannel() = default;
		ModuleChannel(const std::string& id, const ModulValueType type, ModuleBitOffset bitOffset, ModulChannelDirection direction)
			:_Id(id)
			, _BitOffset(bitOffset)
			, _Type(type)
			, _Value(type)
			, _LastValue(type)
			, _Direction(direction)
			, _Event(nullptr)
			
		{
			;
		}

		ModuleChannel(const ModuleChannel& other)
			:_Id(other._Id)
			, _BitOffset(other._BitOffset)
			, _Type(other._Type)
			, _Value(other._Value)
			, _LastValue(other._LastValue)
			, _Direction(other._Direction)
			, _Event(other._Event)
		{

		}

		void registerChannelEvent(ModuleValueChangedEvent* valueChangedEvent)
		{
			_Event = valueChangedEvent;
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

		void setValue(mimodule::ModuleBuffer& iobuffer)
		{
			switch (_Type)
			{
			case ModulValueType::Boolean:
			{
				bool val = iobuffer.getBoolean(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Double:
			{
				double val = iobuffer.getValue<double>(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Float:
			{
				float val = iobuffer.getValue<float>(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Int8:
			{
				int8_t val = iobuffer.getValue<int8_t>(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Int16:
			{
				int16_t val = iobuffer.getValue<int16_t>(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Int32:
			{
				int32_t val = iobuffer.getValue<int32_t>(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Int64:
			{
				int32_t val = iobuffer.getValue<int32_t>(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Uint8:
			{
				uint8_t val = iobuffer.getValue<uint8_t>(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Uint16:
			{
				uint16_t val = iobuffer.getValue<uint16_t>(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Uint32:
			{
				uint32_t val = iobuffer.getValue<uint32_t>(_BitOffset);
				val >> _Value;
				break;
			}
			case ModulValueType::Uint64:
			{
				uint64_t val = iobuffer.getValue<uint64_t>(_BitOffset);
				val >> _Value;
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