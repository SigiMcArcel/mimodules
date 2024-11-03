#pragma once
#include "ModuleBase.h"
#include "ModuleMiPotentiometer.h"

namespace mimodule
{ 
	class ModuleMiPotentiometerMCP4725 :
		public mimodule::ModuleMiPotentiometer
	{

		const double _MCP4725MaxDigits = 1053.0;
	protected:
		virtual int32_t getADCValue();
		virtual void getMaxDigits() override;

	public:
		ModuleMiPotentiometerMCP4725(uint8_t address, double filter, double refVoltage, double maxVoltage, const std::string& name)
			:ModuleMiPotentiometer(address, filter, name, refVoltage, maxVoltage)
			
		{

		}

		uint16_t value();
	};
}

