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
    ModuleBase::open();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::close()
{
    ModuleBase::close();
    _I2CDriver.close();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::readInputsPrivate(bool init)
{
	double dval = static_cast<double>(getADCValue());
    double percent = 100.0 / _MaxDigits * dval;
    double diff = fabs(percent - _LastPercent);
    if((_LastPercent != percent) && (diff > _Filter) || init)
    {
        std::vector<mimodule::ModuleChannel*>::iterator iter;
        for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
        {
            (*iter)->value().setValue<double>(percent,init);
        }
    }
    _LastPercent = percent;

    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::writeOutputsPrivate()
{
    return ModuleResult::Ok;
}
