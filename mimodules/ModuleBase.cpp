#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include "ModuleBase.h"

void mimodule::ModuleBase::setChannel(int pin, ModulValueType type, ModuleBitOffset offset, ModulChannelDirection dir)
{
	std::string name("");
	if (dir == ModulChannelDirection::Input)
	{
		name.append("E");
	}
	else
	{
		name.append("A");
	}

	name.append(std::to_string(_Address));
	name.append(".");
	name.append(std::to_string(pin));
	ModuleChannel* channel = new ModuleChannel(name, type, offset, dir);
	if (dir == ModulChannelDirection::Output)
	{
		channel->registerChannelEvent(this, true);
	}
	_Channels.push_back(channel);
}

int mimodule::ModuleBase::getAddress()
{
	return _Address;
}

const std::string mimodule::ModuleBase::name()
{
	return _Name;
}

const mimodule::ModuleResult mimodule::ModuleBase::state() const
{
	return _State;
}

mimodule::ModuleResult mimodule::ModuleBase::init()
{
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleBase::deinit()
{
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleBase::open()
{
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleBase::close()
{
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleBase::readInputs(bool init)
{
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleBase::writeOutputs()
{
	return ModuleResult::Ok;
}

void mimodule::ModuleBase::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
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
