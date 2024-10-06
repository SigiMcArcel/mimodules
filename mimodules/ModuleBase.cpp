#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include "ModuleBase.h"

mimodule::ModuleResult mimodule::ModuleBase::readInputsPrivate(bool init)
{
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleBase::writeOutputsPrivate()
{
    return ModuleResult::Ok;
}

const mimodule::ModuleResult mimodule::ModuleBase::state() const
{
	return _State;
}

mimodule::ModuleResult mimodule::ModuleBase::open()
{
	switch (_SyncMode)
	{
	case ModuleIOSyncMode::SyncModeNone:
	case ModuleIOSyncMode::SyncModeManager:
	{
		readInputsPrivate(true);
		break;
	}
	case ModuleIOSyncMode::SyncModeModuleFree:
	{
		_CycleTime = 0;
	}
	case ModuleIOSyncMode::SyncModeModuleCyclic:
	{
		readInputsPrivate(true);
		_Timer.Start(_CycleTime);
		break;
	}
	}
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleBase::close()
{
	if ((_SyncMode == ModuleIOSyncMode::SyncModeModuleCyclic) || (_SyncMode == ModuleIOSyncMode::SyncModeModuleFree))
	{
		_Timer.Stop();
	}
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleBase::readInputs(bool init)
{
	if (_SyncMode == ModuleIOSyncMode::SyncModeNone)
	{
		return ModuleResult::Ok;
	}
	if (_SyncMode == ModuleIOSyncMode::SyncModeManager)
	{
		return readInputsPrivate(init);
	}
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleBase::writeOutputs()
{
	if (_SyncMode == ModuleIOSyncMode::SyncModeManager)
	{
		return writeOutputsPrivate();
	}
	return ModuleResult::Ok;
}

// Geerbt über EventListener
void mimodule::ModuleBase::eventOccured(void* sender, const std::string& name)
{
	if (_SyncMode != ModuleIOSyncMode::SyncModeManager)
	{
		readInputsPrivate(false);
		writeOutputsPrivate();
	}
}

mimodule::ModuleChannel* mimodule::ModuleBase::getChannel(std::string id)
{
	ChannelList::iterator iter;
	if (_Channels.empty())
	{
		printf("Module %s: error no Channels");
		return nullptr;
	}
	for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
	{
		if ((*iter)->id() == id)
		{
			return (*iter);
		}
	}
	return nullptr;
}

bool mimodule::ModuleBase::registerChannelEvent(ModuleValueChangedEvent* valueChangedEvent, bool checkChanges, const std::string& id)
{
    std::vector<ModuleChannel*>::iterator iter;
    for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
    {
        if ((*iter)->id() == id)
        {
            (*iter)->registerChannelEvent(valueChangedEvent, checkChanges);
            return true;
        }
    }
    return false;
}
