#include "ModuleMiSevenSegment.h"
#include <cmath>
#include <mi/midriver/DriverBase.h>

namespace
{
    bool contains(const std::string& str, const std::string& substr) {
        return str.find(substr) != std::string::npos;
    }

    uint8_t getLastCharAsInt8(const std::string& str) {
        if (!str.empty()) {
            // Hole das letzte Zeichen und konvertiere es in einen int (ASCII-Wert)
            return static_cast<uint8_t>(std::stoi(str.substr(str.size() - 1)));
        }
        return 0xff;
    }
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::writeCmd(uint8_t command, uint8_t data)
{
    uint8_t cmd[2] = { 0 };
    miDriver::DriverResults result = miDriver::DriverResults::Ok;
    cmd[0] = command;
    cmd[1] = data;
    result = _SPIDriver.transfer(0, 2, cmd, cmd);
    if (result != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorWrite;
    }
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::writeCmd(mimodule::ModuleMiSevenSegmentMaxCommand command, uint8_t data)
{
    return writeCmd(static_cast<uint8_t>(command), data);
}

void mimodule::ModuleMiSevenSegment::setBlank()
{
    for (unsigned char i = 1; i < 9; i++)
    {
        writeCmd(static_cast<mimodule::ModuleMiSevenSegmentMaxCommand>(i), static_cast<uint8_t>(ModuleMiSevenSegmentMaxCommand::Blank));
    }
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::init()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::open()
{
   
    if (_SPIDriver.open() != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    writeCmd(ModuleMiSevenSegmentMaxCommand::DisplayTest, 0);
    writeCmd(ModuleMiSevenSegmentMaxCommand::DecodeMode, 0xff);
    writeCmd(ModuleMiSevenSegmentMaxCommand::ScanLimit, 0x07);
    writeCmd(ModuleMiSevenSegmentMaxCommand::Shutdown, 1);
    writeCmd(ModuleMiSevenSegmentMaxCommand::Intensity, 0x0f);
    setBlank();
    ModuleBase::open();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::close()
{
    ModuleBase::close();
    writeCmd(ModuleMiSevenSegmentMaxCommand::Shutdown, 0);
    _SPIDriver.close();
    return ModuleResult::Ok;
}

void mimodule::ModuleMiSevenSegment::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
    if (contains(id, std::string("Segment")))
    {
        Command cmd;
        cmd.Segment = getLastCharAsInt8(id);
        cmd.SevenSegmentCommand = value.getValue<uint8_t>();

        printf("ModuleMiSevenSegment %d %d \n", cmd.Segment, cmd.SevenSegmentCommand);
        if ((cmd.SevenSegmentCommand < 9) || (cmd.SevenSegmentCommand == 0x0f))
        {
            cmd.Segment = 9 - cmd.Segment;
            writeCmd(cmd.Segment, cmd.SevenSegmentCommand);
        }
    }
    else if(id == "Control")
    {
        Command cmd;
        cmd.ControlCommand = value.getValue<uint32_t>();
        ControlCommand ctrl = static_cast<ControlCommand>(cmd.ControlCommand);
        switch (ctrl)
        {
        case ControlCommand::Blank:
        {
            setBlank();
            break;
        }
        case ControlCommand::None:
        {
            break;
        }
        }
    }
}
mimodule::ModuleResult mimodule::ModuleMiSevenSegment::readInputsPrivate(bool init)
{
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::writeOutputsPrivate()
{
    return ModuleResult::Ok;
}

void  mimodule::ModuleMiSevenSegment::Segment1(unsigned char val) { _OutputBuffer.setValue(val, 0); }
void  mimodule::ModuleMiSevenSegment::Segment2(unsigned char val) { _OutputBuffer.setValue(val, 1); }
void  mimodule::ModuleMiSevenSegment::Segment3(unsigned char val) { _OutputBuffer.setValue(val, 2); }
void  mimodule::ModuleMiSevenSegment::Segment4(unsigned char val) { _OutputBuffer.setValue(val, 3); }
void  mimodule::ModuleMiSevenSegment::Segment5(unsigned char val) { _OutputBuffer.setValue(val, 4); }
void  mimodule::ModuleMiSevenSegment::Segment6(unsigned char val) { _OutputBuffer.setValue(val, 5); }
void  mimodule::ModuleMiSevenSegment::Segment7(unsigned char val) { _OutputBuffer.setValue(val, 6); }
void  mimodule::ModuleMiSevenSegment::Segment8(unsigned char val) { _OutputBuffer.setValue(val, 7); }
void  mimodule::ModuleMiSevenSegment::Control(unsigned int val) { _OutputBuffer.setValue(val, 8); }

