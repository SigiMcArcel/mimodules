#pragma once
#include "ModuleBase.h"
#include <mi/midriver/GPIODriver.h>
#include <mi/miutils/Timer.h>
#include <vector>

namespace mimodule
{ 
	typedef enum class ModuleMiRpiGpioState_e
	{
		Active,
		Inactive,
		Free,
		Used
	}ModuleMiRpiGpioState;

	typedef struct ModuleMiRpiGpioConfiguration_t
	{
		size_t Size;
		ModuleMiRpiGpioState State;
		ModulChannelDirection Dir;
		int Number;

	}ModuleMiRpiGpioConfiguration;

	class ModuleMiRpiGpio : public mimodule::ModuleBase
	{
	private:
		miDriver::GPIODriver _GPIODriver;
		std::vector<ModuleValueChangedEvent*> _Events;
		std::vector<ModuleMiRpiGpioConfiguration> _Configuration;

		void setupGpioPin(mimodule::ModuleMiRpiGpioState state, mimodule::ModulChannelDirection dir, int pinNumber);
		void setup();
		ModuleMiRpiGpioConfiguration* findGPIO(std::vector<ModuleMiRpiGpioConfiguration>& condiguration, int number);
		void configure(std::vector<ModuleMiRpiGpioConfiguration>& condiguration);


	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputsPrivate(bool init) override;
		virtual ModuleResult writeOutputsPrivate() override;
		virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id);

	public:
		ModuleMiRpiGpio(const std::string& name, const std::vector<ModuleMiRpiGpioConfiguration>& condiguration, mimodule::ModuleIOSyncMode syncMode, int cycleTime)
			:ModuleBase(name, 2, 0, syncMode, cycleTime)
			, _GPIODriver()
			, _Configuration(condiguration)
		{
			setup();
			configure(_Configuration);
		}
	};
}

