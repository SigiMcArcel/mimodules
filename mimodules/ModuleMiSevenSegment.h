#pragma once
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
		DisplayTest
	}ModuleMiSevenSegmentMaxCommand;
	class ModuleMiSevenSegment :
		public mimodule::ModuleBase
	{
	private:
		std::string _Device;
		miDriver::SPIDriver _SPIDriver;

		ModuleResult writeCmd(mimodule::ModuleMiSevenSegmentMaxCommand command, unsigned char data);
		void setBlank();

	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs(bool init);
		virtual ModuleResult writeOutputs();

	public:
	

		typedef enum class controlCommand_t
		{
			None,
			Blank
		}controlCommand;


		ModuleMiSevenSegment(const std::string& device,const std::string& name)
			:ModuleBase(2, 0, name)
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
			_Channels.push_back(new ModuleChannel("Control", ModulValueType::Uint8, 0, ModulChannelDirection::Output));
	
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

