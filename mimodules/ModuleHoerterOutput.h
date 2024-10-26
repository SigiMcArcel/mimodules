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
		std::vector<ModuleValueChangedEvent*> _Events;

		void setupChannels(int num)
		{
			for (int i = 0; i < num; i++)
			{
				setChannel(i, ModulValueType::Boolean, static_cast<ModuleBitOffset>(i), ModulChannelDirection::Output);
			}
		}

	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs(bool init) override;
		virtual ModuleResult writeOutputs() override;
		virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id)  override;

	public:
		ModuleHoerterOutput(uint8_t address, const std::string& name)
			:ModuleBase(name, 0, 1, address)
			, _I2CDriver(address)	
		{
			setupChannels(8);
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


