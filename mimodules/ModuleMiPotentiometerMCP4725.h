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
		ModuleMiPotentiometerMCP4725(uint8_t address, double filter, const std::string& name, mimodule::ModuleIOSyncMode syncMode, int cycleTime)
			:ModuleMiPotentiometer(address, filter, name, 5000.0, 5000.0, _MCP4725MaxDigits, 0)
			
		{

		}

		uint16_t value();
	};
}

