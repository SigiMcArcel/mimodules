#include "ModuleManager.h"

void mimodule::ModuleManager::start()
{
	for (mimodule::ModuleInterface* mod : _Modules)
	{
		mod->init();
		mod->open();
	}
	_IOTimer.Start();
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

bool mimodule::ModuleManager::timerEventOccured(void* sender, const std::string& name)
{
	if ("IOTimer" == name)
	{
		for (mimodule::ModuleInterface* mod : _Modules)
		{
			mod->readInputs(false);
			mod->writeOutputs();
		}
	}
	return false;
}
