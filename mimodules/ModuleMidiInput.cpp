#include "ModuleMidiInput.h"

mimodule::ModuleResult mimodule::ModuleMidiInput::init()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMidiInput::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMidiInput::open()
{
    if (_Midi == nullptr)
    {
        return ModuleResult::ErrorInvalidBuffer;
    }
    if (_Midi->open() != miDriver::DriverResults_e::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    ModuleBase::open();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMidiInput::close()
{
    ModuleBase::close();
    if (_Midi == nullptr)
    {
        return ModuleResult::ErrorInvalidBuffer;
    }
    _Midi->close();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMidiInput::readInputs(bool init)
{
    miDriver::MidiMessage message;
    if (_Midi == nullptr)
    {
        return ModuleResult::ErrorInvalidBuffer;
    }
    while (_Midi->read(message) == miDriver::DriverResults_e::Ok)
    {
        if (message.U.Message.StatusByte.Channel == _MidiChannel)
        {
            if (message.U.Message.StatusByte.Command == miDriver::MidiCommand_e::NoteOn)
            {
                if (message.U.Message.Velocity > 0)
                {
                    //_Channels[message.U.Message.Key].
                    bool val = true;
                    _Channels[message.U.Message.Key]->value().setValue(val,init);
                }
                else
                {
                    bool val = false;
                    _Channels[message.U.Message.Key]->value().setValue(val,init);
                }
                if (_Channels[message.U.Message.Key]->valueChangedEvent())
                {
                    _Channels[message.U.Message.Key]->valueChangedEvent()->ValueChanged(
                        _Channels[message.U.Message.Key]->value(), _Channels[message.U.Message.Key]->id());
                }
            }
          
        }
    }
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMidiInput::writeOutputs()
{
    return ModuleResult::Ok;
}