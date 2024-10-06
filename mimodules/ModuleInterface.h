#pragma once
#include <string>
#include "ModuleTypes.h"

namespace mimodule
{
	class ModuleValue;
	class ModuleValueChangedEvent
	{
	public:
		virtual void ValueChanged(mimodule::ModuleValue& value,const std::string& id) = 0;
	};

	class ModuleInterface
	{
	public:
		virtual mimodule::ModuleResult init() = 0;
		virtual mimodule::ModuleResult deinit() = 0;
		virtual mimodule::ModuleResult open() = 0;
		virtual mimodule::ModuleResult close() = 0;
		virtual mimodule::ModuleResult readInputs(bool init) = 0;
		virtual mimodule::ModuleResult writeOutputs() = 0;
	};
}


