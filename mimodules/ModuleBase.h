#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <typeinfo>
#include <memory>
#include <mi/miutils/Timer.h>
#include "ModuleBuffer.h"
#include "ModuleChannel.h"
#include "ModuleInterface.h"
#include "ModuleTypes.h"

/// <summary>
/// Interface for machina imaginis control
/// abstracts several IO's or IO Interfaces like gpio.SPI,i2c etc
/// Used in CIModul
/// </summary>
/// 

namespace mimodule
{
	typedef std::vector<ModuleChannel*> ChannelList;
	class ModuleBase 
	: public ModuleInterface
	, public miutils::EventListener
	{
		friend class ModuleManager;
	protected:
		std::string _Name;
		ModuleResult _State;
		int _MaxInputBitSize;
		int _MaxOutputBitSize;
		ModuleBuffer _InputBuffer;
		ModuleBuffer _LastInputBuffer;
		ModuleBuffer _OutputBuffer;
		ModuleBuffer _LastOutputBuffer;
		ChannelList _Channels;
		miutils::Timer _Timer;
		mimodule::ModuleIOSyncMode _SyncMode;
		int _CycleTime;

		virtual mimodule::ModuleResult readInputsPrivate(bool init);
		virtual mimodule::ModuleResult writeOutputsPrivate();

	public:
		ModuleBase(const std::string& name,ModuleByteSize inputSize, ModuleByteSize outputSize)
			:_Name(name)
			,_State(ModuleResult::Ok)
			,_MaxInputBitSize(inputSize)
			,_MaxOutputBitSize(outputSize)
			, _InputBuffer(inputSize)
			, _LastInputBuffer(inputSize)
			, _OutputBuffer(outputSize)
			, _LastOutputBuffer(outputSize)
			, _Timer("IO",this)
			, _SyncMode(mimodule::ModuleIOSyncMode::SyncModeManager)
			, _CycleTime(0)
		{
			
		};

		ModuleBase(const std::string& name,ModuleByteSize inputSize, ModuleByteSize outputSize,mimodule::ModuleIOSyncMode syncMode,int cycleTime)
			:_Name(name)
			, _State(ModuleResult::Ok)
			, _MaxInputBitSize(inputSize)
			, _MaxOutputBitSize(outputSize)
			, _InputBuffer(inputSize)
			, _LastInputBuffer(inputSize)
			, _OutputBuffer(outputSize)
			, _LastOutputBuffer(outputSize)
			, _Timer("IO", this)
			, _SyncMode(syncMode)
			, _CycleTime(cycleTime)
		{

		};

		ModuleBase()
			:_Name("Modul")
			, _State(ModuleResult::Ok)
			, _MaxInputBitSize(0)
			, _MaxOutputBitSize(0)
			, _InputBuffer(0)
			, _LastInputBuffer(0)
			, _OutputBuffer(0)
			, _LastOutputBuffer(0)
			, _Timer("IO", this)
			, _SyncMode(mimodule::ModuleIOSyncMode::SyncModeManager)
		{
			
		};

		~ModuleBase() = default;
		const ModuleResult state() const;
		ModuleChannel* getChannel(std::string id);
		bool registerChannelEvent(ModuleValueChangedEvent* valueChangedEvent, bool checkChanges, const std::string& id);

		virtual mimodule::ModuleResult open();
		virtual mimodule::ModuleResult close();
		virtual mimodule::ModuleResult readInputs(bool init);
		virtual mimodule::ModuleResult writeOutputs();
		
		// Geerbt über EventListener
		virtual void eventOccured(void* sender, const std::string& name) override;

		
	};

	
}

