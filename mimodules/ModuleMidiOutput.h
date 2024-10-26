#pragma once
#include <mi/midriver/MidiDriver.h>
#include "ModuleBase.h"
namespace mimodule
{
	class ModuleMidiOutput : public mimodule::ModuleBase
	{
	private:
		miDriver::MidiDriver* _Midi;
		uint8_t _MidiChannel;

	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs(bool init) override;
		virtual ModuleResult writeOutputs() override;
		virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override;

	public:
		ModuleMidiOutput(uint8_t channel, const std::string& name)
			:ModuleBase(name, 0, 8)
			, _Midi(miDriver::MidiDriver::GetInstance("/dev/snd/midiC1D0"))
			, _MidiChannel(channel)
		{
			_Channels.push_back(new ModuleChannel("A1", ModulValueType::Boolean, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A2", ModulValueType::Boolean, 1, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A3", ModulValueType::Boolean, 2, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A4", ModulValueType::Boolean, 3, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A5", ModulValueType::Boolean, 4, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A6", ModulValueType::Boolean, 5, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A7", ModulValueType::Boolean, 6, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A8", ModulValueType::Boolean, 7, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A9", ModulValueType::Boolean, 8, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A10", ModulValueType::Boolean, 9, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A11", ModulValueType::Boolean, 10, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A12", ModulValueType::Boolean, 11, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A13", ModulValueType::Boolean, 12, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A14", ModulValueType::Boolean, 13, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A15", ModulValueType::Boolean, 14, ModulChannelDirection::Output));

			_Channels.push_back(new ModuleChannel("A16", ModulValueType::Boolean, 15, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A17", ModulValueType::Boolean, 16, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A18", ModulValueType::Boolean, 17, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A19", ModulValueType::Boolean, 18, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A20", ModulValueType::Boolean, 19, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A21", ModulValueType::Boolean, 20, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A22", ModulValueType::Boolean, 21, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A23", ModulValueType::Boolean, 22, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A24", ModulValueType::Boolean, 23, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A25", ModulValueType::Boolean, 24, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A26", ModulValueType::Boolean, 25, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A27", ModulValueType::Boolean, 26, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A28", ModulValueType::Boolean, 27, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A29", ModulValueType::Boolean, 28, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A30", ModulValueType::Boolean, 29, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A31", ModulValueType::Boolean, 30, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A32", ModulValueType::Boolean, 31, ModulChannelDirection::Output));

			_Channels.push_back(new ModuleChannel("A33", ModulValueType::Boolean, 32, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A34", ModulValueType::Boolean, 33, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A35", ModulValueType::Boolean, 34, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A36", ModulValueType::Boolean, 35, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A37", ModulValueType::Boolean, 36, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A38", ModulValueType::Boolean, 37, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A39", ModulValueType::Boolean, 38, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A40", ModulValueType::Boolean, 39, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A41", ModulValueType::Boolean, 40, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A42", ModulValueType::Boolean, 41, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A43", ModulValueType::Boolean, 42, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A44", ModulValueType::Boolean, 43, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A45", ModulValueType::Boolean, 44, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A46", ModulValueType::Boolean, 45, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A47", ModulValueType::Boolean, 46, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A48", ModulValueType::Boolean, 47, ModulChannelDirection::Output));

			_Channels.push_back(new ModuleChannel("A49", ModulValueType::Boolean, 48, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A50", ModulValueType::Boolean, 49, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A51", ModulValueType::Boolean, 50, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A52", ModulValueType::Boolean, 51, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A53", ModulValueType::Boolean, 52, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A54", ModulValueType::Boolean, 53, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A55", ModulValueType::Boolean, 54, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A56", ModulValueType::Boolean, 55, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A57", ModulValueType::Boolean, 56, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A58", ModulValueType::Boolean, 57, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A59", ModulValueType::Boolean, 58, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A60", ModulValueType::Boolean, 59, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A61", ModulValueType::Boolean, 60, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A62", ModulValueType::Boolean, 61, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A63", ModulValueType::Boolean, 62, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("A64", ModulValueType::Boolean, 63, ModulChannelDirection::Output));
		}
	};
}


