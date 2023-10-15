#pragma once
#include <stdint.h>
#include <string>
#include "ModuleTypes.h"
#include "ModulePointer.h"
#include <cstring>

namespace mimodule
{
	class ModuleBuffer
	{
	private:
		ModuleByteSize _Size;
		ModulePointer _Pointer;
		ModuleResult _Result;
		
	public:
		
		ModuleBuffer(const ModuleBuffer& other)
			:_Size(other._Size)
			, _Pointer(other._Pointer)
			, _Result(mimodule::ModuleResult::Ok)
		{
			
		}

		ModuleBuffer(ModuleByteSize size)
			:_Size(size)
			, _Pointer(size,"")
			, _Result(mimodule::ModuleResult::Ok)
		{
			

		}

		~ModuleBuffer()
		{
			
			
		}

		unsigned char* buffer()
		{
			return static_cast<unsigned char*>(_Pointer.pointer());
		}

		void cpyTo(ModuleBuffer& obj)
		{
			/*if (_Pointer == nullptr)
			{
				_Result = ModuleResult::ErrorInvalidBuffer;

				return;
			}*/
			if (_Size == obj._Size)
			{
				::memcpy(obj._Pointer.pointer(), _Pointer.pointer(), _Size);
			}
		}

		template <typename T>
		T getValue(ModuleBitOffset offset)
		{
			ModuleBitOffset byteOffset = offset / 8;
			if (!_Pointer.valid())
			{
				_Result = ModuleResult::ErrorInvalidBuffer;
				return T();
			}
			if (_Size < (sizeof(T) + (unsigned long)byteOffset) || (!_Pointer.valid()))
			{
				_Result = ModuleResult::ErrorBufferRangeExceeded;
				return T();
			}
			return *((T*)(_Pointer.pointer() + byteOffset));
		}
		template <typename T>
		void setValue(T value, ModuleBitOffset offset)
		{
			ModuleBitOffset byteOffset = offset / 8;
			if (!_Pointer.valid())
			{
				_Result = ModuleResult::ErrorInvalidBuffer;
				return;
			}
			if (_Size < (sizeof(T) + ((unsigned long)byteOffset)) || (!_Pointer.valid()))
			{
				_Result = ModuleResult::ErrorBufferRangeExceeded;
				return;
			}
			*((T*)(_Pointer.pointer() + byteOffset)) = value;
		}

		bool getBoolean(ModuleBitOffset offset)
		{
			uint32_t byteVal = static_cast<uint32_t>(getValue<uint8_t>(offset));
			uint32_t bitNumber = static_cast<uint32_t>((offset % 8));
			if ((byteVal & (1 << bitNumber)) > 0)
			{
				return true;
			}
			return false;
		}

		void  setBoolean(bool val, ModuleBitOffset offset)
		{
			uint32_t byteVal = static_cast<uint32_t>(getValue<uint8_t>(offset));
			uint32_t bitNumber = static_cast<uint32_t>((offset % 8));
			if (val)
			{
				byteVal = byteVal | (1 << bitNumber);
			}
			else
			{
				byteVal = byteVal & ~(1 << bitNumber);
			}
			
			setValue<uint8_t>((uint8_t)byteVal, offset);

		}

		bool operator!=(ModuleBuffer& obj)
		{
			for (uint16_t i = 0; i < _Size; i++)
			{
				if (getValue<uint8_t>(i) != obj.getValue<uint8_t>(i))
				{
					return true;
				}
			}
			return false;
		}

		
		
	};
}

