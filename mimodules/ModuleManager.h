#pragma once
#include <vector>
#include "ModuleInterface.h"
#include "ModuleTypes.h"
#include <mi/miutils/Timer.h>

namespace mimodule
{
	class ModuleManager : public miutils::TimerEventListener
	{
	private:
		miutils::Timer _IOTimer;
		std::vector<mimodule::ModuleInterface*> _Modules;
		int32_t _CycleTime;
	public:
		ModuleManager() = default;
		ModuleManager(int32_t cycletime)
			:_IOTimer("IOTimer", _CycleTime, 0, 10, miutils::SchedulerType::Fifo,this)
			,_CycleTime(cycletime)
		{

		}
		void start();
		void stop();
		// SyncModeSync
		void addModule(mimodule::ModuleInterface* module);

		// Geerbt über EventListener
		virtual bool timerEventOccured(void* sender, const std::string& name) override;

	};
}

