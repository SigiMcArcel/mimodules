#include "ModuleMiPhoneNumber.h"
#include <cmath>
mimodule::ModuleResult mimodule::ModuleMiPhoneNumber::init()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiPhoneNumber::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiPhoneNumber::open()
{
    if (_GPIODriver.GpioEnable(_GpioPinStart,true) != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    if (_GPIODriver.GpioSetDirection(_GpioPinStart, miDriver::GPIODirection::Input) != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    if (_GPIODriver.GpioEnable(_GpioPinPulse, true) != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    if (_GPIODriver.GpioSetDirection(_GpioPinPulse, miDriver::GPIODirection::Input) != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }

    _Timer.Start(_CycleTime);
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPhoneNumber::close()
{
    _Timer.Stop();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPhoneNumber::readInputs()
{   
    if (_LastChoosedNumber != _ChoosedNumber)
    { 
        std::vector<mimodule::ModuleChannel*>::iterator iter;

        iter = _Channels.begin();
        _ChoosedNumber >> (*iter)->value();
        if ((*iter)->valueChangedEvent() != nullptr)
        {
            (*iter)->valueChangedEvent()->ValueChanged((*iter)->value(), (*iter)->id());
        }

    }
    _LastChoosedNumber = _ChoosedNumber;
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPhoneNumber::writeOutputs()
{
    return ModuleResult::Ok;
}

int mimodule::ModuleMiPhoneNumber::value()
{
    return _ChoosedNumber;
}

void mimodule::ModuleMiPhoneNumber::eventOccured(void* sender, const std::string& name)
{
    if ("phone" == name)
    {
        bool stateStart = _GPIODriver.GpioRead(_GpioPinStart);
        bool statePulse = _GPIODriver.GpioRead(_GpioPinPulse);
        if (stateStart && _LastStart)
        {
            if (!_RflagStart)
            {
                _RflagStart = 1;
                _FlagCount = 0;
            }
        }

        if (!stateStart && !_LastStart)
        {
            if (_RflagStart)
            {
                _RflagStart = 0;
                if (_FlagCount == 10)
                {
                    _ChoosedNumber = 0;
                }
                else
                {
                    _ChoosedNumber = _FlagCount;
                }

                printf("ChoosedNumber %d\n", _ChoosedNumber);
               
            }

        }
        _LastStart = stateStart;
        if (statePulse && _LastPulse)
        {
            if (!_RflagPulse)
            {
                _RflagPulse = 1;
            }
        }

        if (!statePulse && !_LastPulse)
        {
            if (_RflagPulse)
            {
                _RflagPulse = 0;
                _FlagCount++;
            }
        }
        _LastPulse = statePulse;
    }

}
