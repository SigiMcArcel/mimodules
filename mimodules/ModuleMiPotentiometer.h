#pragma once
#include "ModuleBase.h"
#include <mi/midriver/I2CDriver.h>

namespace mimodule
{ 
	class ModuleMiPotentiometer :
		public mimodule::ModuleBase
	{
		
	protected:
		miDriver::I2CDriver _I2CDriver;
		uint8_t _Address;
		double _Filter;
		double _LastPercent;
		std::vector<ModuleValueChangedEvent*> _Events;
		double _VoltageRangeADC;
		double _MaxAnalogVoltageInput;
		double _MaxDigitsADC;
		double _MaxDigits;

		virtual int32_t getADCValue() = 0;
		virtual void getMaxDigits() = 0;
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs(bool init);
		virtual ModuleResult writeOutputs();
	public:
		ModuleMiPotentiometer(uint8_t address,
			double filter,
			const std::string& name,
			double voltageRangeADC,
			double maxAnalogVoltageInput,
			double maxDigitsADC,
			double maxDigits
			)
			:ModuleBase(8, 0, name)
			, _I2CDriver(address)
			, _Address(address)
			, _Filter(filter)
			, _LastPercent(0)
			, _VoltageRangeADC(voltageRangeADC)
			, _MaxAnalogVoltageInput(maxAnalogVoltageInput)
			, _MaxDigitsADC(maxDigitsADC)
			, _MaxDigits(maxDigits)

		{
			_Channels.push_back(new ModuleChannel("Potentiometer", ModulValueType::Double, 0, ModulChannelDirection::Input));
		}

		uint16_t value();
	};
}

