#include "ModuleMiPotentiometer.h"
#include <cmath>
mimodule::ModuleResult mimodule::ModuleMiPotentiometer::init()
{
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

mimodule::ModuleResult mimodule::ModuleMiPotentiometer::readInputs()
{
    if (_I2CDriver.read(2, _InputBuffer.buffer()) != miDriver::DriverResults::Ok)
    {
        _InputBuffer.cpyTo(_LastInputBuffer);
        return ModuleResult::ErrorRead;
    }
    if (_LastInputBuffer != _InputBuffer)
    {
        std::vector<mimodule::ModuleChannel*>::iterator iter;
        for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
        {
            uint16_t val = _InputBuffer.getValue<uint16_t>((*iter)->bitOffset());
            uint16_t valLast = _LastInputBuffer.getValue<uint16_t>((*iter)->bitOffset());
            int32_t val32 = (int32_t)val;
            int32_t lastVal32 = (int32_t)valLast;
            int32_t absVal = std::abs((lastVal32 - val32));


            if (absVal > (int32_t)_Filter)
            {
                val >> (*iter)->value();
                if ((*iter)->valueChangedEvent() != nullptr)
                {
                    (*iter)->valueChangedEvent()->ValueChanged((*iter)->value(), (*iter)->id());
                }
            }
        }
    }
    _InputBuffer.cpyTo(_LastInputBuffer);


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
