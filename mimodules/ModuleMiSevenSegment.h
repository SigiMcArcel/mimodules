#pragma once
#include <vector>
#include "ModuleBase.h"
#include <mi/midriver/SPIDriver.h>

namespace mimodule
{ 
	typedef enum class ModuleMiSevenSegmentMaxCommand_t
	{
		NOOP,
		Digit0,
		Digit1,
		Digit2,
		Digit3,
		Digit4,
		Digit5,
		Digit6,
		Digit7,
		DecodeMode,
		Intensity,
		ScanLimit,
		Shutdown,
		DisplayTest,
		Blank = 15
	}ModuleMiSevenSegmentMaxCommand;

	class ModuleMiSevenSegment 
		:public mimodule::ModuleBase
		,public mimodule::ModuleValueChangedEvent
	{
	private:
		typedef struct Command_t
		{
			uint8_t  SevenSegmentCommand;
			uint32_t ControlCommand;
			uint8_t  Segment;
			Command_t()
				:SevenSegmentCommand(0)
				,ControlCommand(0)
				,Segment(0)
			{

			}
		}Command;

		std::string _Device;
		miDriver::SPIDriver _SPIDriver;
		
		ModuleResult writeCmd(uint8_t command, uint8_t data);
		ModuleResult writeCmd(mimodule::ModuleMiSevenSegmentMaxCommand command, uint8_t data);
		void setBlank();

	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs(bool init) override;
		virtual ModuleResult writeOutputs() override;
		virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id);

	public:
		typedef enum class controlCommand_t
		{
			None,
			Blank
		}ControlCommand;

		ModuleMiSevenSegment(const std::string& device,const std::string& name)
			:ModuleBase(name, 2, 0)
			, _SPIDriver(miDriver::SPIModes::SPIMode0,250000, miDriver::SPIBitsPerWord::SPI8Bits,device)
		{
			_Channels.push_back(new ModuleChannel("Segment1", ModulValueType::Uint8, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("Segment2", ModulValueType::Uint8, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("Segment3", ModulValueType::Uint8, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("Segment4", ModulValueType::Uint8, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("Segment5", ModulValueType::Uint8, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("Segment6", ModulValueType::Uint8, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("Segment7", ModulValueType::Uint8, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("Segment8", ModulValueType::Uint8, 0, ModulChannelDirection::Output));
			_Channels.push_back(new ModuleChannel("Control" , ModulValueType::Uint8, 0, ModulChannelDirection::Output));

			registerChannelEvent(this,false, "Segment1");
			registerChannelEvent(this,false, "Segment2");
			registerChannelEvent(this, false, "Segment3");
			registerChannelEvent(this, false, "Segment4");
			registerChannelEvent(this, false, "Segment5");
			registerChannelEvent(this, false, "Segment6");
			registerChannelEvent(this, false, "Segment7");
			registerChannelEvent(this, false, "Segment8");
			registerChannelEvent(this, false, "Control" );
		}

		void Segment1(unsigned char val);
		void Segment2(unsigned char val);
		void Segment3(unsigned char val);
		void Segment4(unsigned char val);
		void Segment5(unsigned char val);
		void Segment6(unsigned char val);
		void Segment7(unsigned char val);
		void Segment8(unsigned char val);
		void Control(unsigned int val);
		
	};
}

