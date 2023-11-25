#pragma once
#include <mi/midriver/MidiDriver.h>
#include "ModuleBase.h"

namespace mimodule
{
	class ModuleMidiInput : public mimodule::ModuleBase
	{
	private:
		miDriver::MidiDriver*  _Midi;
		uint8_t _MidiChannel;
		


	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs();
		virtual ModuleResult writeOutputs();

	public:
		ModuleMidiInput(uint8_t channel, const std::string& name)
			:ModuleBase(8, 0, name)
			, _Midi(miDriver::MidiDriver::GetInstance("/dev/snd/midiC1D0"))
			, _MidiChannel(channel)
		{
			_Channels.push_back(new ModuleChannel("E1", ModulValueType::Boolean, 0, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E2", ModulValueType::Boolean, 1, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E3", ModulValueType::Boolean, 2, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E4", ModulValueType::Boolean, 3, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E5", ModulValueType::Boolean, 4, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E6", ModulValueType::Boolean, 5, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E7", ModulValueType::Boolean, 6, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E8", ModulValueType::Boolean, 7, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E9", ModulValueType::Boolean, 8, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E10", ModulValueType::Boolean, 9, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E11", ModulValueType::Boolean, 10, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E12", ModulValueType::Boolean, 11, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E13", ModulValueType::Boolean, 12, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E14", ModulValueType::Boolean, 13, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E15", ModulValueType::Boolean, 14, ModulChannelDirection::Input));

			_Channels.push_back(new ModuleChannel("E16", ModulValueType::Boolean, 15, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E17", ModulValueType::Boolean, 16, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E18", ModulValueType::Boolean, 17, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E19", ModulValueType::Boolean, 18, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E20", ModulValueType::Boolean, 19, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E21", ModulValueType::Boolean, 20, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E22", ModulValueType::Boolean, 21, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E23", ModulValueType::Boolean, 22, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E24", ModulValueType::Boolean, 23, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E25", ModulValueType::Boolean, 24, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E26", ModulValueType::Boolean, 25, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E27", ModulValueType::Boolean, 26, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E28", ModulValueType::Boolean, 27, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E29", ModulValueType::Boolean, 28, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E30", ModulValueType::Boolean, 29, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E31", ModulValueType::Boolean, 30, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E32", ModulValueType::Boolean, 31, ModulChannelDirection::Input));

			_Channels.push_back(new ModuleChannel("E33", ModulValueType::Boolean, 32, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E34", ModulValueType::Boolean, 33, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E35", ModulValueType::Boolean, 34, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E36", ModulValueType::Boolean, 35, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E37", ModulValueType::Boolean, 36, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E38", ModulValueType::Boolean, 37, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E39", ModulValueType::Boolean, 38, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E40", ModulValueType::Boolean, 39, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E41", ModulValueType::Boolean, 40, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E42", ModulValueType::Boolean, 41, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E43", ModulValueType::Boolean, 42, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E44", ModulValueType::Boolean, 43, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E45", ModulValueType::Boolean, 44, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E46", ModulValueType::Boolean, 45, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E47", ModulValueType::Boolean, 46, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E48", ModulValueType::Boolean, 47, ModulChannelDirection::Input));

			_Channels.push_back(new ModuleChannel("E49", ModulValueType::Boolean, 48, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E50", ModulValueType::Boolean, 49, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E51", ModulValueType::Boolean, 50, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E52", ModulValueType::Boolean, 51, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E53", ModulValueType::Boolean, 52, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E54", ModulValueType::Boolean, 53, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E55", ModulValueType::Boolean, 54, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E56", ModulValueType::Boolean, 55, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E57", ModulValueType::Boolean, 56, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E58", ModulValueType::Boolean, 57, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E59", ModulValueType::Boolean, 58, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E60", ModulValueType::Boolean, 59, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E61", ModulValueType::Boolean, 60, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E62", ModulValueType::Boolean, 61, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E63", ModulValueType::Boolean, 62, ModulChannelDirection::Input));
			_Channels.push_back(new ModuleChannel("E64", ModulValueType::Boolean, 63, ModulChannelDirection::Input));
		}
	};

}