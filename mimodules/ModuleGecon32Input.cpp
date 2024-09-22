#include "ModuleGecon32Input.h"
#include "ModuleChannel.h"


mimodule::ModuleResult mimodule::ModuleGecon32Input::init()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleGecon32Input::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleGecon32Input::open()
{
    if (_ModbusDriver->open() != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleGecon32Input::close()
{
    _ModbusDriver->close();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleGecon32Input::readInputs(bool init)
{
    
    if(_ModbusDriver->readInputBits(_Address,32,miDriver::ModbusDriverAccessType_e::BITS, _InputBuffer.buffer()) != miDriver::DriverResults::Ok)
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
            bool valLast = _LastInputBuffer.getBoolean((*iter)->bitOffset());
            if ((val != valLast) || init)
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

mimodule::ModuleResult mimodule::ModuleGecon32Input::writeOutputs()
{
    return ModuleResult::Ok;
}

bool mimodule::ModuleGecon32Input::E1() { return _InputBuffer.getBoolean(0); }
bool mimodule::ModuleGecon32Input::E2() { return _InputBuffer.getBoolean(1); }
bool mimodule::ModuleGecon32Input::E3() { return _InputBuffer.getBoolean(2); }
bool mimodule::ModuleGecon32Input::E4() { return _InputBuffer.getBoolean(3); }
bool mimodule::ModuleGecon32Input::E5() { return _InputBuffer.getBoolean(4); }
bool mimodule::ModuleGecon32Input::E6() { return _InputBuffer.getBoolean(5); }
bool mimodule::ModuleGecon32Input::E7() { return _InputBuffer.getBoolean(6); }
bool mimodule::ModuleGecon32Input::E8() { return _InputBuffer.getBoolean(7);}
bool mimodule::ModuleGecon32Input::E9() { return _InputBuffer.getBoolean(8); }
bool mimodule::ModuleGecon32Input::E10() { return _InputBuffer.getBoolean(9); }
bool mimodule::ModuleGecon32Input::E11() { return _InputBuffer.getBoolean(10); }
bool mimodule::ModuleGecon32Input::E12() { return _InputBuffer.getBoolean(11); }
bool mimodule::ModuleGecon32Input::E13() { return _InputBuffer.getBoolean(12); }
bool mimodule::ModuleGecon32Input::E14() { return _InputBuffer.getBoolean(13); }
bool mimodule::ModuleGecon32Input::E15() { return _InputBuffer.getBoolean(14); }
bool mimodule::ModuleGecon32Input::E16() { return _InputBuffer.getBoolean(15); }
bool mimodule::ModuleGecon32Input::E17() { return _InputBuffer.getBoolean(16); }
bool mimodule::ModuleGecon32Input::E18() { return _InputBuffer.getBoolean(17); }
bool mimodule::ModuleGecon32Input::E19() { return _InputBuffer.getBoolean(18); }
bool mimodule::ModuleGecon32Input::E20() { return _InputBuffer.getBoolean(19); }
bool mimodule::ModuleGecon32Input::E21() { return _InputBuffer.getBoolean(20); }
bool mimodule::ModuleGecon32Input::E22() { return _InputBuffer.getBoolean(21); }
bool mimodule::ModuleGecon32Input::E23() { return _InputBuffer.getBoolean(22); }
bool mimodule::ModuleGecon32Input::E24() { return _InputBuffer.getBoolean(23); }
bool mimodule::ModuleGecon32Input::E25() { return _InputBuffer.getBoolean(24); }
bool mimodule::ModuleGecon32Input::E26() { return _InputBuffer.getBoolean(25); }
bool mimodule::ModuleGecon32Input::E27() { return _InputBuffer.getBoolean(26); }
bool mimodule::ModuleGecon32Input::E28() { return _InputBuffer.getBoolean(27); }
bool mimodule::ModuleGecon32Input::E29() { return _InputBuffer.getBoolean(28); }
bool mimodule::ModuleGecon32Input::E30() { return _InputBuffer.getBoolean(29); }
bool mimodule::ModuleGecon32Input::E31() { return _InputBuffer.getBoolean(30); }
bool mimodule::ModuleGecon32Input::E32() { return _InputBuffer.getBoolean(31); }

