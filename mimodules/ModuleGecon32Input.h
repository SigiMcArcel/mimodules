#pragma once
#include <vector>
#include <string>
#include <mi/midriver/ModbusDriver.h>
#include "ModuleBase.h"

namespace mimodule
{
	class ModuleGecon32Input : public mimodule::ModuleBase
	{
	private:
		miDriver::ModbusDriver *_ModbusDriver;
		std::string _Device;
		
		void setupChannels(int num)
		{
			for (int i = 0; i < num; i++)
			{
				setChannel(i, ModulValueType::Boolean, static_cast<ModuleBitOffset>(i), ModulChannelDirection::Input);
			}
		}
		
	protected:
		virtual ModuleResult open() override;
		virtual ModuleResult close() override;
		virtual ModuleResult readInputs(bool init) override;
		virtual ModuleResult writeOutputs() override;

	public:
		ModuleGecon32Input(const std::string& device,int address,const std::string& name)
			:ModuleBase(name,4, 0, address)
			, _Device(device)
		{
			_ModbusDriver =  miDriver::ModbusDriver::GetInstance(_Device);
			setupChannels(32);
		}

		bool E1();
		bool E2();
		bool E3();
		bool E4();
		bool E5();
		bool E6();
		bool E7();
		bool E8();
		bool E9();
		bool E10();
		bool E11();
		bool E12();
		bool E13();
		bool E14();
		bool E15();
		bool E16();
		bool E17();
		bool E18();
		bool E19();
		bool E20();
		bool E21();
		bool E22();
		bool E23();
		bool E24();
		bool E25();
		bool E26();
		bool E27();
		bool E28();
		bool E29();
		bool E30();
		bool E31();
		bool E32();

	};
}

