#pragma once
#include "ModuleBase.h"
#include "ModuleMiPotentiometer.h"
#include <mi/midriver/I2CDriver.h>

namespace mimodule
{ 
	class ModuleMiPotentiometerADS1115 :
		public mimodule::ModuleMiPotentiometer
	{
	private:
		typedef enum class ADS1115ConversionMode_e
		{
			Continuous = 0,
			SingleShot = 1
		}ADS1115ConversionMod;

		typedef enum class ADS1115Channel_e
		{
			ANC0,
			ANC1,
			ANC2,
			ANC3
		}ADS1115Channel;

		typedef enum class ADS1115DataRate_e
		{
			SPS8 = 0,
			SPS16 = 1,
			SPS32 = 2,
			SPS64 = 3,
			SPS128 = 4,
			SPS250 = 5,
			SPS475 = 6,
			SPS860 = 7
		}ADS1115DataRate;

		typedef enum class ADS1115Gains_e
		{
			Gain6144mv,
			Gain4096mv,
			Gain2048mv,
			Gain1024mv,
			Gain0512mv,
			Gain0256mv,
			Gain0256mv2,
			Gain0256mv3,
			GainMax
		}ADS1115Gains;

		const double GainRanges[8] =
		{
			6144.0,
			4096.0,
			2048.0,
			1024.0,
			512.0,
			256.0,
			256.0,
			256.0
		};

		const double _ADS115MaxDigits = 32767.0;

		// bit 15 flag bit for single shot
		// Bits 14-12 input selection:
		// 100 ANC0; 101 ANC1; 110 ANC2; 111 ANC3
		// Bits 11-9 Amp gain. Default to 010 here 001 P19
		// Bit 8 Operational mode of the ADS1115.
		// 0 : Continuous conversion mode
		// 1 : Power-down single-shot mode (default)
		// Bits 7-5 data rate default to 100 for 128SPS
		// Bits 4-0  comparator functions see spec sheet
		typedef union ADS1115Config_u
		{
			uint8_t data[2];
			struct reg_t
			{
				uint8_t COMP_QUE : 2;
				uint8_t COMP_LAT : 1;
				uint8_t COMP_POL : 1;
				uint8_t COMP_MODE : 1;
				uint8_t DR : 3;
				uint8_t MODE : 1;
				uint8_t PGA : 3;
				uint8_t MUX : 3;
				uint8_t OS : 1;
			}Reg;
		}ADS1115Config;
		
		uint8_t _Gain;
		uint8_t getGain(double gainAsVoltage);

	protected:
		virtual int32_t getADCValue();
		void getMaxDigits() override;

	public:
		ModuleMiPotentiometerADS1115(uint8_t address, double filter,double maxVoltage,const std::string& name)
			:ModuleMiPotentiometer(address,filter,name,4096.0, maxVoltage,_ADS115MaxDigits,0)
			, _Gain(getGain(_VoltageRangeADC))
		{
			
		}
	};
}

