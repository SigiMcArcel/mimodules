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


mimodule::ModuleResult mimodule::ModuleMiPotentiometer::readInputs(bool init)
{
	double dval = static_cast<double>(getADCValue());
    double vval = _VoltageReferenceADC / _MaxDigits * dval;
    double percent = 100.0 / _MaxDigits * dval;
    double diff = fabs(percent - _LastPercent);
    if(((_LastPercent != percent) && (diff > _Filter)) || init)
    {
        std::vector<mimodule::ModuleChannel*>::iterator iter;
        for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
        {
            if(((*iter)->id() == "Potentiometer") || ((*iter)->id() == "Potentiometer"))
            {
                (*iter)->value().setValue<double>(percent, init);
            }
            else if ((*iter)->id() == "PotentiometerDigits")
            {
                (*iter)->value().setValue<double>(dval, init);
            }
            else if ((*iter)->id() == "PotentiometerVoltage")
            {
                (*iter)->value().setValue<double>(vval, init);
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
