#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <typeinfo>
#include <memory>
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
	class ModuleBase : public ModuleInterface
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

		
		
	public:
		ModuleBase(ModuleByteSize inputSize, ModuleByteSize outputSize,const std::string& name)
			:_Name(name)
			,_State(ModuleResult::Ok)
			,_MaxInputBitSize(inputSize)
			,_MaxOutputBitSize(outputSize)
			, _InputBuffer(inputSize)
			, _LastInputBuffer(inputSize)
			, _OutputBuffer(outputSize)
			, _LastOutputBuffer(outputSize)

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
		const ModuleResult state() const
		{
			return _State;
		}

		
		bool registerChannelEvent(ModuleValueChangedEvent* valueChangedEvent, const std::string& id);

		ModuleChannel* getChannel(std::string id)
		{
			ChannelList::iterator iter;
			for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
			{
				if ((*iter)->id() == id)
				{
					return (*iter);
				}
			}
			return nullptr;
		}
	};
}

