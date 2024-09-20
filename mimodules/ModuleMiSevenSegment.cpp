#include "ModuleMiSevenSegment.h"
#include <cmath>
#include <mi/midriver/DriverBase.h>

bool contains(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}
int getLastCharAsInt(const std::string& str) {
    if (!str.empty()) {
        // Hole das letzte Zeichen und konvertiere es in einen int (ASCII-Wert)
        return std::stoi(str.substr(str.size() - 1));
    }
    return -1;
}


mimodule::ModuleResult mimodule::ModuleMiSevenSegment::writeCmd(mimodule::ModuleMiSevenSegmentMaxCommand command, unsigned char data)
{
    unsigned char cmd[2] = { 0 };
    miDriver::DriverResults result = miDriver::DriverResults::Ok;
    cmd[0] = static_cast<unsigned char>(command);
    cmd[1] = data;
    result = _SPIDriver.transfer(0, 2, cmd, cmd);
    if (result != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorWrite;
    }
    return ModuleResult();
}

void mimodule::ModuleMiSevenSegment::setBlank()
{
    for (unsigned char i = 1; i < 9; i++)
    {
        writeCmd(static_cast<mimodule::ModuleMiSevenSegmentMaxCommand>(i), 0x0f);
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
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::close()
{
    writeCmd(ModuleMiSevenSegmentMaxCommand::Shutdown, 0);
    _SPIDriver.close();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::readInputs(bool init)
{
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiSevenSegment::writeOutputs()
{
    ChannelList::iterator iterChannels;
   
    for (iterChannels = _Channels.begin(); iterChannels < _Channels.end(); ++iterChannels)
    {
        unsigned char u8Value = 0;
        unsigned char u32Value = 0;
        controlCommand ctrl = controlCommand::Blank;

        if ((*iterChannels)->value().changed())
        {
            if (contains((*iterChannels)->id(), std::string("Segment")))
            {
                int seg = getLastCharAsInt((*iterChannels)->id());
               
                u8Value << (*iterChannels)->value();
                writeCmd(static_cast<ModuleMiSevenSegmentMaxCommand>((9 - seg)), u8Value);
            }
            else
            {
                u32Value << (*iterChannels)->value();
                ctrl = static_cast<controlCommand>(u32Value);
                switch (ctrl)
                {
                case controlCommand::Blank:
                {
                    setBlank();
                    break;
                }
                case controlCommand::None:
                {
                    break;;
                }
                }
            }
        }
    }

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

