#pragma once
#include "ModuleBase.h"
#include </mi/midriver/I2CDriver.h>

namespace mimodule
{ 
	class ModuleMiPotentiometer :
		public mimodule::ModuleBase
	{
	private:
		miDriver::I2CDriver _I2CDriver;
		uint8_t _Address;
		uint16_t _Filter;
		std::vector<ModuleValueChangedEvent*> _Events;


	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs();
		virtual ModuleResult writeOutputs();
	public:
		ModuleMiPotentiometer(uint8_t address, uint16_t filter,const std::string& name)
			:ModuleBase(2, 0, name)
			, _I2CDriver(address)
			, _Address(address)
			,_Filter(filter)

		{
			_Channels.push_back(new ModuleChannel("Potentiometer", ModulValueType::Uint16, 0, ModulChannelDirection::Input));
		}

		uint16_t value();
	};
}

