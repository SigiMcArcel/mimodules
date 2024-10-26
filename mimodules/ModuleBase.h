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
	, public mimodule::ModuleValueChangedEvent
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
		uint8_t _Address;

		void setChannel(int pin, ModulValueType type, ModuleBitOffset offset, ModulChannelDirection dir);

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
			, _Address(0)
		{
			
		};

		ModuleBase(const std::string& name, ModuleByteSize inputSize, ModuleByteSize outputSize,uint8_t address)
			:_Name(name)
			, _State(ModuleResult::Ok)
			, _MaxInputBitSize(inputSize)
			, _MaxOutputBitSize(outputSize)
			, _InputBuffer(inputSize)
			, _LastInputBuffer(inputSize)
			, _OutputBuffer(outputSize)
			, _LastOutputBuffer(outputSize)
			, _Address(address)
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
		{
			
		};

		~ModuleBase() = default;
		const ModuleResult state() const;
		ModuleChannel* getChannel(std::string id);
		int getAddress();
		bool registerChannelEvent(ModuleValueChangedEvent* valueChangedEvent, bool checkChanges, const std::string& id);

		virtual const std::string name() override;
		virtual mimodule::ModuleResult init() override;
		virtual mimodule::ModuleResult deinit() override;
		virtual mimodule::ModuleResult open() override;
		virtual mimodule::ModuleResult close() override;
		virtual mimodule::ModuleResult readInputs(bool init) override;
		virtual mimodule::ModuleResult writeOutputs() override;
		virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override;
	};
}

