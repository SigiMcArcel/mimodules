#pragma once

#include <string>
#include <stdint.h>
#include "ModulePointer.h"


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
	private:
		ModulePointer _Buffer;
		ModulValueType _Type;
		bool _Changed;

	public:

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
			, _Changed(false)
		{

		}

		ModuleValue(ModulValueType type)
			:_Buffer(getSizeFromType(type),  "")
			, _Type(type)
			, _Changed(false)
		{

		}

		ModuleValue(const ModuleValue& other)
			: _Buffer(other._Buffer)
			, _Type(other._Type)
			, _Changed(other._Changed)
		{

		}

		~ModuleValue()
		{

		}


		const bool changed() const
		{
			return _Changed;
		}
		friend bool& operator<<(bool& value, ModuleValue& moduleValue)
		{

			value = *((bool*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}


		friend bool& operator>>(bool& value, ModuleValue& moduleValue)
		{
			bool tmp = *((uint8_t*)(moduleValue._Buffer.pointer()));
			if (tmp != value)
			{
				*((bool*)(moduleValue._Buffer.pointer())) = value;

				moduleValue._Changed = true;
			}
			
			return value;
		}

		friend uint8_t& operator<<(uint8_t& value, ModuleValue& moduleValue)
		{
			value = *((uint8_t*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend uint8_t& operator>>(uint8_t& value, ModuleValue& moduleValue)
		{
			*((uint8_t*)(moduleValue._Buffer.pointer())) = value;
			moduleValue._Changed = true;
			return value;
		}

		friend uint16_t& operator<<(uint16_t& value, ModuleValue& moduleValue)
		{
			value = *((uint16_t*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend uint16_t& operator>>(uint16_t& value, ModuleValue& moduleValue)
		{
			*((uint16_t*)(moduleValue._Buffer.pointer())) = value;
			moduleValue._Changed = true;
			return value;
		}

		friend uint32_t& operator<<(uint32_t& value, ModuleValue& moduleValue)
		{
			value = *((uint32_t*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend uint32_t& operator>>(uint32_t& value, ModuleValue& moduleValue)
		{
			*((uint32_t*)(moduleValue._Buffer.pointer())) = value;
			moduleValue._Changed = true;
			return value;
		}

		friend uint64_t& operator<<(uint64_t& value, ModuleValue& moduleValue)
		{
			value = *((uint64_t*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend uint64_t& operator>>(uint64_t& value, ModuleValue& moduleValue)
		{
			*((uint64_t*)(moduleValue._Buffer.pointer())) = value;
			moduleValue._Changed = true;
			return value;
		}

		friend int8_t& operator<<(int8_t& value, ModuleValue& moduleValue)
		{
			value = *((int8_t*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend int8_t& operator>>(int8_t& value, ModuleValue& moduleValue)
		{
			*((int8_t*)(moduleValue._Buffer.pointer())) = value;
			moduleValue._Changed = true;
			return value;
		}

		friend int16_t& operator<<(int16_t& value, ModuleValue& moduleValue)
		{
			value = *((int16_t*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend int16_t& operator>>(int16_t& value, ModuleValue& moduleValue)
		{
			*((int16_t*)(moduleValue._Buffer.pointer())) = value;
			moduleValue._Changed = true;
			return value;
		}

		friend int32_t& operator<<(int32_t& value, ModuleValue& moduleValue)
		{
			value = *((int32_t*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend int32_t& operator>>(int32_t& value, ModuleValue& moduleValue)
		{
			*((int32_t*)(moduleValue._Buffer.pointer())) = value;
			moduleValue._Changed = true;
			return value;
		}
		
		friend int64_t& operator<<(int64_t& value, ModuleValue& moduleValue)
		{
			value = *((int64_t*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend int64_t& operator>>(int64_t& value, ModuleValue& moduleValue)
		{
			*((int64_t*)(moduleValue._Buffer.pointer())) = value;
			moduleValue._Changed = true;
			return value;
		}

		friend float& operator<<(float& value, ModuleValue& moduleValue)
		{
			value = *((float*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend float& operator>>(float& value, ModuleValue& moduleValue)
		{
			*((float*)(moduleValue._Buffer.pointer())) = value;
			moduleValue._Changed = true;
			return value;
		}

		friend double& operator<<(double& value, ModuleValue& moduleValue)
		{
			value = *((double*)(moduleValue._Buffer.pointer()));
			moduleValue._Changed = false;
			return value;
		}

		friend double& operator>>(double& value, ModuleValue& moduleValue)
		{
			*((double*)(moduleValue._Buffer.pointer())) = value;
			
			moduleValue._Changed = true;
			return value;
		}

		
	};
}

