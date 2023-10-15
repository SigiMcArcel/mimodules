#pragma once
#include <string>
#include <cstring>
#include <stdint.h>

namespace mimodule
{
	class ModulePointer
	{
	private:
		uint8_t* _Pointer;
		int32_t _InstanceCounter;
		int32_t _WeakCounter;
		int32_t _Size;
		std::string _Id;
		bool _Valid;



	public:
		ModulePointer()
			:_Pointer(nullptr)
			, _InstanceCounter(-1)
			, _WeakCounter(-1)
			, _Size(-1)
			, _Id("")
			, _Valid(false)
		{

		}


		ModulePointer(int32_t size,const std::string& id)
			:_Pointer(nullptr)
			, _InstanceCounter(0)
			, _WeakCounter(0)
			, _Size(size)
			, _Id(id)
			, _Valid(false)
		{
			_Pointer = (uint8_t*)std::malloc(_Size);
			if (_Pointer != nullptr)
			{
				_Valid = true;
			}
		}

		ModulePointer(const ModulePointer& other)
			:_Pointer(other._Pointer)
			, _InstanceCounter(other._InstanceCounter)
			, _WeakCounter(other._WeakCounter)
			, _Size(other._Size)
			, _Id(other._Id)
			, _Valid(other._Valid)
		{
			_InstanceCounter++;
		}

		~ModulePointer()
		{
			_InstanceCounter--;
			if (_InstanceCounter == 0)
			{
				free(_Pointer);
			}
		}

		ModulePointer& operator=(ModulePointer& other)
		{
			_InstanceCounter = 0;
			_WeakCounter = 0;
			_Size = other._Size;
			
			if (_Pointer != nullptr)
			{
				std::memcpy(_Pointer, other._Pointer, _Size);
				_Valid = true;
				return *this;
			}
			_Valid = false;
			return *this;
		}

		uint8_t* pointer()
		{
			return _Pointer;
		}

		bool valid()
		{
 			return _Valid;
		}

	};
}

