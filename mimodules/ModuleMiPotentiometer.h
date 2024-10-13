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

	public:
		ModuleMiPotentiometer(uint8_t address,
			double filter,
			const std::string& name,
			double voltageRangeADC,
			double maxAnalogVoltageInput,
			double maxDigitsADC,
			double maxDigits)
			:ModuleBase(name, 8, 0)
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

		virtual ModuleResult init() override;
		virtual ModuleResult deinit() override;
		virtual ModuleResult open() override;
		virtual ModuleResult close() override;
		virtual ModuleResult readInputs(bool init) override;
		virtual ModuleResult writeOutputs() override;
	};
}

