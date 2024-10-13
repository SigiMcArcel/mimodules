#include "ModuleHoerterInput.h"
#include "ModuleChannel.h"


mimodule::ModuleResult mimodule::ModuleHoerterInput::init()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleHoerterInput::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleHoerterInput::open()
{
    if (_I2CDriver.open() != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    ModuleBase::open();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleHoerterInput::close()
{
    ModuleBase::close();
    _I2CDriver.close();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleHoerterInput::readInputs(bool init)
{
    if(_I2CDriver.read(1, _InputBuffer.buffer()) != miDriver::DriverResults::Ok)
    {
        _InputBuffer.cpyTo(_LastInputBuffer);
        return ModuleResult::ErrorRead;
    }
    if (_LastInputBuffer != _InputBuffer)
    {
        std::vector<mimodule::ModuleChannel*>::iterator iter;
        for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
        {
            bool val = _InputBuffer.getBoolean((*iter)->bitOffset());
            (*iter)->value().setValue(val,init);
        }
    }
    _InputBuffer.cpyTo(_LastInputBuffer);


    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleHoerterInput::writeOutputs()
{
    return ModuleResult::Ok;
}


bool mimodule::ModuleHoerterInput::E1()
{
    return _InputBuffer.getBoolean(0);
}
bool mimodule::ModuleHoerterInput::E2()
{
    return _InputBuffer.getBoolean(1);
}
bool mimodule::ModuleHoerterInput::E3()
{
    return _InputBuffer.getBoolean(2);
}
bool mimodule::ModuleHoerterInput::E4()
{
    return _InputBuffer.getBoolean(3);;
}
bool mimodule::ModuleHoerterInput::E5()
{
    return _InputBuffer.getBoolean(4);
}
bool mimodule::ModuleHoerterInput::E6()
{
    return _InputBuffer.getBoolean(5);
}
bool mimodule::ModuleHoerterInput::E7()
{
    return _InputBuffer.getBoolean(6);
}
bool mimodule::ModuleHoerterInput::E8()
{
    return _InputBuffer.getBoolean(7);
}


