#pragma once
#include "ModuleBase.h"
#include <mi/midriver/GPIODriver.h>
#include <mi/miutils/Timer.h>

namespace mimodule
{ 
	class ModuleMiPhoneNumber :
		public mimodule::ModuleBase
	{
	private:
		miDriver::GPIODriver _GPIODriver;
		std::vector<ModuleValueChangedEvent*> _Events;
		int _ChoosedNumber;
		bool _ChoosedNumberChanged;
		int _GpioPinStart;
		int _GpioPinPulse;
		int _LastPulse;
		int _LastStart;
		int _FlagCount;
		int _RflagStart;
		int _RflagPulse;

	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputsPrivate(bool init) override;
		virtual ModuleResult writeOutputsPrivate() override;
	public:
		ModuleMiPhoneNumber( int cycleTime,const std::string& name,int pinStart,int pinPulse, mimodule::ModuleIOSyncMode syncMode)
			:ModuleBase(name, 2, 0, syncMode, cycleTime)
			, _GPIODriver()
			, _Events()
			, _ChoosedNumber(0)
			, _ChoosedNumberChanged(false)
			, _GpioPinStart(pinStart)
			, _GpioPinPulse(pinPulse)
			, _LastPulse(0)
			, _LastStart(0)
			, _FlagCount(0)
			, _RflagStart(0)
			, _RflagPulse(0)
		{
			_Channels.push_back(new ModuleChannel("PhoneNumber", ModulValueType::Uint8, 0, ModulChannelDirection::Input));
		}

		// Geerbt über EventListener
		virtual void eventOccured(void* sender, const std::string& name) override;

		int value();
	};
}

