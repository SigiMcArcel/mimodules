#pragma once
#include <vector>
#include <string>
#include <mi/midriver/I2CDriver.h>
#include "ModuleBase.h"

namespace mimodule
{
	
	class ModuleHoerterOutput : public mimodule::ModuleBase
	{
	private:
		miDriver::I2CDriver _I2CDriver;
		uint8_t _Address;
		std::vector<ModuleValueChangedEvent*> _Events;


	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs(bool init);
		virtual ModuleResult writeOutputs();

	public:
		ModuleHoerterOutput(uint8_t address, const std::string& name)
			:ModuleBase(1, 1,name)
			, _I2CDriver(address)
			, _Address(address)
	
		{
			_Channels.push_back(new ModuleChannel("A1", ModulValueType::Boolean, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A2", ModulValueType::Boolean, 1, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A3", ModulValueType::Boolean, 2, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A4", ModulValueType::Boolean, 3, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A5", ModulValueType::Boolean, 4, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A6", ModulValueType::Boolean, 5, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A7", ModulValueType::Boolean, 6, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A8", ModulValueType::Boolean, 7, ModulChannelDirection::Output));
		}

		void A1(bool val);
		void A2(bool val);
		void A3(bool val);
		void A4(bool val);
		void A5(bool val);
		void A6(bool val);
		void A7(bool val);
		void A8(bool val);
		



	};
}


