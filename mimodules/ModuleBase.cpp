#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream
#include "ModuleBase.h"


bool mimodule::ModuleBase::registerChannelEvent(ModuleValueChangedEvent* valueChangedEvent, const std::string& id)
{
    std::vector<ModuleChannel*>::iterator iter;
    for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
    {
        if ((*iter)->id() == id)
        {
            (*iter)->registerChannelEvent(valueChangedEvent);
            return true;
        }
    }
    return false;
}
