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
		double _VoltageReferenceADC;
		double _MaxAnalogVoltageInput;
		double _MaxDigits;

		virtual int32_t getADCValue() = 0;
		virtual void getMaxDigits() = 0;

	public:
		ModuleMiPotentiometer(uint8_t address,
			double filter,
			const std::string& name,
			double voltageReferenceADC,
			double maxAnalogVoltageInput)
			:ModuleBase(name, 8, 0)
			, _I2CDriver(address)
			, _Address(address)
			, _Filter(filter)
			, _LastPercent(0)
			, _VoltageReferenceADC(voltageReferenceADC)
			, _MaxAnalogVoltageInput(maxAnalogVoltageInput)
		{
			_Channels.push_back(new ModuleChannel("Potentiometer", ModulValueType::Double, 0, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("PotentiometerPercent", ModulValueType::Double, 0, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("PotentiometerVoltage", ModulValueType::Double, 0, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("PotentiometerDigits", ModulValueType::Double, 0, ModulChannelDirection::Input));
		}

		virtual ModuleResult init() override;
		virtual ModuleResult deinit() override;
		virtual ModuleResult open() override;
		virtual ModuleResult close() override;
		virtual ModuleResult readInputs(bool init) override;
		virtual ModuleResult writeOutputs() override;
	};
}

