#pragma once
#include <vector>
#include <string>
#include <mi/midriver/I2CDriver.h>
#include "ModuleBase.h"


namespace mimodule
{
	class ModuleHoerterInput : public mimodule::ModuleBase
	{
	private:
		miDriver::I2CDriver _I2CDriver;
		
	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs(bool init) override;
		virtual ModuleResult writeOutputs() override;
		
		void setupChannels(int num)
		{
			for (int i = 0; i < num; i++)
			{
				setChannel(i, ModulValueType::Boolean, static_cast<ModuleBitOffset>(i), ModulChannelDirection::Input);
			}
		}

	public:
		ModuleHoerterInput(uint8_t address,const std::string& name)
			:ModuleBase(name, 1, 0, address)
			,_I2CDriver(address)
		{
			setupChannels(8);
		}

		bool E1();
		bool E2();
		bool E3();
		bool E4();
		bool E5();
		bool E6();
		bool E7();
		bool E8();

		
	};
}

