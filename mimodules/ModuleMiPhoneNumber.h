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

		void getNumbers();

	protected:
		virtual ModuleResult init() override;
		virtual ModuleResult deinit();
		virtual ModuleResult open()override;
		virtual ModuleResult close()override;
		virtual ModuleResult readInputs(bool init) override;
		virtual ModuleResult writeOutputs() override;
	public:
		ModuleMiPhoneNumber( int cycleTime,const std::string& name,int pinStart,int pinPulse)
			:ModuleBase(name, 2, 0)
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

		int value();
	};
}

