#include "ModuleGecon32Output.h"
#include "ModuleChannel.h"


mimodule::ModuleResult mimodule::ModuleGecon32Output::init()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleGecon32Output::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleGecon32Output::open()
{
    if (_ModbusDriver->open() != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    ModuleBase::open();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleGecon32Output::close()
{
    ModuleBase::close();
    _ModbusDriver->close();
    return ModuleResult::Ok;
}

void mimodule::ModuleGecon32Output::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
    bool val = false;
    val = value.getValue<bool>();
    _OutputBuffer.setBoolean(val, getChannel(id)->bitOffset());
}

mimodule::ModuleResult mimodule::ModuleGecon32Output::readInputsPrivate(bool init)
{
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleGecon32Output::writeOutputsPrivate()
{
    if (_OutputBuffer != _LastOutputBuffer)
    {
        if (_ModbusDriver->writeBits(_Address, miDriver::ModbusDriverAccessType_e::BITS, 32, _OutputBuffer.buffer()) != miDriver::DriverResults::Ok)
        {
            printf("writeOutputs  error %s\n", _Name.c_str());

            _OutputBuffer.cpyTo(_LastOutputBuffer);
            return ModuleResult::ErrorWrite;
        }
    }
    _OutputBuffer.cpyTo(_LastOutputBuffer);
    return ModuleResult::Ok;
}

void  mimodule::ModuleGecon32Output::A1(bool val) { _OutputBuffer.setBoolean(!val,0); }
void  mimodule::ModuleGecon32Output::A2(bool val) { _OutputBuffer.setBoolean(!val, 1); }
void  mimodule::ModuleGecon32Output::A3(bool val) { _OutputBuffer.setBoolean(!val, 2); }
void  mimodule::ModuleGecon32Output::A4(bool val) { _OutputBuffer.setBoolean(!val, 3); }
void  mimodule::ModuleGecon32Output::A5(bool val) { _OutputBuffer.setBoolean(!val, 4); }
void  mimodule::ModuleGecon32Output::A6(bool val) { _OutputBuffer.setBoolean(!val, 5); }
void  mimodule::ModuleGecon32Output::A7(bool val) { _OutputBuffer.setBoolean(!val, 6); }
void  mimodule::ModuleGecon32Output::A8(bool val) { _OutputBuffer.setBoolean(!val, 7); }
void  mimodule::ModuleGecon32Output::A9(bool val) { _OutputBuffer.setBoolean(!val, 8); }
void  mimodule::ModuleGecon32Output::A10(bool val) { _OutputBuffer.setBoolean(!val, 9); }
void  mimodule::ModuleGecon32Output::A11(bool val) { _OutputBuffer.setBoolean(!val, 10); }
void  mimodule::ModuleGecon32Output::A12(bool val) { _OutputBuffer.setBoolean(!val, 11); }
void  mimodule::ModuleGecon32Output::A13(bool val) { _OutputBuffer.setBoolean(!val, 12); }
void  mimodule::ModuleGecon32Output::A14(bool val) { _OutputBuffer.setBoolean(!val, 13); }
void  mimodule::ModuleGecon32Output::A15(bool val) { _OutputBuffer.setBoolean(!val, 14); }
void  mimodule::ModuleGecon32Output::A16(bool val) { _OutputBuffer.setBoolean(!val, 15); }
void  mimodule::ModuleGecon32Output::A17(bool val) { _OutputBuffer.setBoolean(!val, 16); }
void  mimodule::ModuleGecon32Output::A18(bool val) { _OutputBuffer.setBoolean(!val, 17); }
void  mimodule::ModuleGecon32Output::A19(bool val) { _OutputBuffer.setBoolean(!val, 18); }
void  mimodule::ModuleGecon32Output::A20(bool val) { _OutputBuffer.setBoolean(!val, 19); }
void  mimodule::ModuleGecon32Output::A21(bool val) { _OutputBuffer.setBoolean(!val, 20); }
void  mimodule::ModuleGecon32Output::A22(bool val) { _OutputBuffer.setBoolean(!val, 21); }
void  mimodule::ModuleGecon32Output::A23(bool val) { _OutputBuffer.setBoolean(!val, 22); }
void  mimodule::ModuleGecon32Output::A24(bool val) { _OutputBuffer.setBoolean(!val, 23); }
void  mimodule::ModuleGecon32Output::A25(bool val) { _OutputBuffer.setBoolean(!val, 24); }
void  mimodule::ModuleGecon32Output::A26(bool val) { _OutputBuffer.setBoolean(!val, 25); }
void  mimodule::ModuleGecon32Output::A27(bool val) { _OutputBuffer.setBoolean(!val, 26); }
void  mimodule::ModuleGecon32Output::A28(bool val) { _OutputBuffer.setBoolean(!val, 27); }
void  mimodule::ModuleGecon32Output::A29(bool val) { _OutputBuffer.setBoolean(!val, 28); }
void  mimodule::ModuleGecon32Output::A30(bool val) { _OutputBuffer.setBoolean(!val, 29); }
void  mimodule::ModuleGecon32Output::A31(bool val) { _OutputBuffer.setBoolean(!val, 30); }
void  mimodule::ModuleGecon32Output::A32(bool val) { _OutputBuffer.setBoolean(!val, 31); }



