#pragma once
#include "ModuleBase.h"
#include <mi/midriver/GPIODriver.h>
#include <mi/miutils/Timer.h>

namespace mimodule
{ 
	class ModuleMiPhoneNumber :
		public mimodule::ModuleBase,
		public miutils::EventListener
	{
	private:
		miDriver::GPIODriver _GPIODriver;
		int _CycleTime;
		miutils::Timer _Timer;
		std::vector<ModuleValueChangedEvent*> _Events;
		int _ChoosedNumber;
		int _LastChoosedNumber;
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
		virtual ModuleResult readInputs(bool init);
		virtual ModuleResult writeOutputs();
	public:
		ModuleMiPhoneNumber( int cycletime,const std::string& name,int pinStart,int pinPulse)
			:ModuleBase(2, 0, name)
			, _GPIODriver()
			, _CycleTime(cycletime)
			, _Timer("phone",this)
			, _Events()
			,_ChoosedNumber(0)
			, _LastChoosedNumber(0)
			,_GpioPinStart(pinStart)
			,_GpioPinPulse(pinPulse)
			,_LastPulse(0)
			,_LastStart(0)
			,_FlagCount(0)
			,_RflagStart(0)
			,_RflagPulse(0)
		{
			_Channels.push_back(new ModuleChannel("PhoneNumber", ModulValueType::Uint8, 0, ModulChannelDirection::Input));
		}

		// Geerbt über EventListener
		virtual void eventOccured(void* sender, const std::string& name) override;

		int value();
	};
}

