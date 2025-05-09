#include "ModuleHoerterOutput.h"

mimodule::ModuleResult mimodule::ModuleHoerterOutput::init()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleHoerterOutput::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleHoerterOutput::open()
{
    if (_I2CDriver.open() != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    _OutputBuffer.setValue<uint8_t>(0xff,0);
    ModuleBase::open();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleHoerterOutput::close()
{
    ModuleBase::close();
    _I2CDriver.close();
    return ModuleResult::Ok;
}

void mimodule::ModuleHoerterOutput::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
    bool val = false;
    val = value.getValue<bool>();
    //hoerter Outputs are inverted
    val = !val;
    _OutputBuffer.setBoolean(val, getChannel(id)->bitOffset());
}

mimodule::ModuleResult mimodule::ModuleHoerterOutput::readInputs(bool init)
{
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleHoerterOutput::writeOutputs()
{
    if (_OutputBuffer != _LastOutputBuffer)
    {
        if (_I2CDriver.write(1, _OutputBuffer.buffer()) != miDriver::DriverResults::Ok)
        {
            printf("writeOutputs  error %s\n", _Name.c_str());

            _OutputBuffer.cpyTo(_LastOutputBuffer);
            return ModuleResult::ErrorWrite;
        } 
    }
    _OutputBuffer.cpyTo(_LastOutputBuffer);
    return ModuleResult::Ok;
}

void  mimodule::ModuleHoerterOutput::A1(bool val)
{
    _OutputBuffer.setBoolean(!val,0);
}
void mimodule::ModuleHoerterOutput::A2(bool val)
{
    _OutputBuffer.setBoolean(!val, 1);
}
void mimodule::ModuleHoerterOutput::A3(bool val)
{
    _OutputBuffer.setBoolean(!val, 2);
}
void mimodule::ModuleHoerterOutput::A4(bool val)
{
    _OutputBuffer.setBoolean(!val, 3);
}
void mimodule::ModuleHoerterOutput::A5(bool val)
{
    _OutputBuffer.setBoolean(!val, 4);
}
void mimodule::ModuleHoerterOutput::A6(bool val)
{
    _OutputBuffer.setBoolean(!val, 5);
}
void mimodule::ModuleHoerterOutput::A7(bool val)
{
    _OutputBuffer.setBoolean(!val, 6);
}
void mimodule::ModuleHoerterOutput::A8(bool val)
{
    _OutputBuffer.setBoolean(!val, 7);
}


