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
		uint8_t _Address;
		
		
		
	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputsPrivate(bool init) override;
		virtual ModuleResult writeOutputsPrivate() override;
		

	public:
		ModuleHoerterInput(uint8_t address,const std::string& name, mimodule::ModuleIOSyncMode syncMode, int cycleTime)
			:ModuleBase(name, 1, 0, syncMode, cycleTime)
			,_I2CDriver(address)
			,_Address(address)
		{
			_Channels.push_back(new ModuleChannel("E1", ModulValueType::Boolean, 0, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E2", ModulValueType::Boolean, 1, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E3", ModulValueType::Boolean, 2, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E4", ModulValueType::Boolean, 3, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E5", ModulValueType::Boolean, 4, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E6", ModulValueType::Boolean, 5, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E7", ModulValueType::Boolean, 6, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E8", ModulValueType::Boolean, 7, ModulChannelDirection::Input));
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

