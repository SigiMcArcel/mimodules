#include "ModuleMiPotentiometer.h"
#include <cmath>

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::init()
{
   getMaxDigits();
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::open()
{
    if (_I2CDriver.open() != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::close()
{
    _I2CDriver.close();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::readInputs(bool init)
{
	double dval = getADCValue();
    double percent = 100.0 / _MaxDigits * dval;
    double diff = fabs(percent - _LastPercent);
    if(((_LastPercent != percent) || init) && (diff > _Filter))
    {
        std::vector<mimodule::ModuleChannel*>::iterator iter;
        for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
        {
            percent >> (*iter)->value();
            if ((*iter)->valueChangedEvent() != nullptr)
            {
                (*iter)->valueChangedEvent()->ValueChanged((*iter)->value(), (*iter)->id());
            }
        }
    }
    _LastPercent = percent;

    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::writeOutputs()
{
    return ModuleResult::Ok;
}

uint16_t mimodule::ModuleMiPotentiometer::value()
{
    return _InputBuffer.getValue<uint16_t>(0);
}
