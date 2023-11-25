#include "ModuleMidiOutput.h"

mimodule::ModuleResult mimodule::ModuleMidiOutput::init()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMidiOutput::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMidiOutput::open()
{
    miDriver::MidiMessage Resetmessage;
    if (_Midi == nullptr)
    {
        return ModuleResult::ErrorInvalidBuffer;
    }
    if (_Midi->open() != miDriver::DriverResults_e::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    Resetmessage.U.MessageRaw[0] = 0xff;
    Resetmessage.Len = 1;
    _Midi->write(Resetmessage);
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMidiOutput::close()
{
    if (_Midi == nullptr)
    {
        return ModuleResult::ErrorInvalidBuffer;
    }
    _Midi->close();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMidiOutput::readInputs()
{
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMidiOutput::writeOutputs()
{
    ChannelList::iterator iterChannels;
    if (_Midi == nullptr)
    {
        return ModuleResult::ErrorInvalidBuffer;
    }
    for (iterChannels = _Channels.begin(); iterChannels < _Channels.end(); ++iterChannels)
    {
        if ((*iterChannels)->value().changed())
        {
            bool val = false;
           
            val << (*iterChannels)->value();
            miDriver::MidiMessage message;
            message.U.Message.Key = static_cast<unsigned char>((*iterChannels)->bitOffset());
            message.U.Message.Velocity = 127;
            message.U.Message.StatusByte.Channel = static_cast<unsigned char>(_MidiChannel);
            message.Len = 3;
            if (val)
            {
                message.U.Message.StatusByte.Command = miDriver::MidiCommand_e::NoteOn;
            }
            else
            {
                message.U.Message.StatusByte.Command = miDriver::MidiCommand_e::NoteOff;
            }
            _Midi->write(message);
        }
    }

    return ModuleResult::Ok;
}
