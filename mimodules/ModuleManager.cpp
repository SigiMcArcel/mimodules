#include "ModuleManager.h"

void mimodule::ModuleManager::start()
{
	for (mimodule::ModuleInterface* mod : _Modules)
	{
		mod->init();
		mod->open();
	}
	_IOTimer.Start(_CycleTime,nullptr,10,miutils::Schedulers::Fifo);
}

void mimodule::ModuleManager::stop()
{
	_IOTimer.Stop();
	for (mimodule::ModuleInterface* mod : _Modules)
	{
		mod->close();
		mod->deinit();
	}
}

void mimodule::ModuleManager::addModule(mimodule::ModuleInterface* module)
{
	_Modules.push_back(module);
}

void mimodule::ModuleManager::eventOccured(void* sender, const std::string& name)
{
	if ("IOTimer" == name)
	{
		for (mimodule::ModuleInterface* mod : _Modules)
		{
			mod->readInputs();
			mod->writeOutputs();
		}
	}
	
}
