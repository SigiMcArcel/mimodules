#pragma once
#include <vector>
#include <string>
#include <mi/midriver/ModbusDriver.h>
#include "ModuleBase.h"

namespace mimodule
{
	class ModuleGecon32Output : public mimodule::ModuleBase
	{
	private:
		miDriver::ModbusDriver* _ModbusDriver;
		std::string _Device;
		int _Address;

		void setChannel(int pin, ModulValueType type, ModuleBitOffset offset, ModulChannelDirection dir)
		{
			std::string name("A");
			name.append(std::to_string(pin));
			printf("%s create output channel pin %d offset %d name %s\n", __func__, pin, offset,name.c_str());
			_Channels.push_back(new ModuleChannel(name, type, offset, dir));
		}

		void setupChannels(int num)
		{
			for (int i = 0; i < num; i++)
			{
				setChannel(i, ModulValueType::Boolean, static_cast<ModuleBitOffset>(i), ModulChannelDirection::Output);
			}
		}


	protected:
		virtual ModuleResult init();
		virtual ModuleResult deinit();
		virtual ModuleResult open();
		virtual ModuleResult close();
		virtual ModuleResult readInputs();
		virtual ModuleResult writeOutputs();

	public:
		ModuleGecon32Output(const std::string& device, int address, const std::string& name)
			:ModuleBase(0, 4, name)
			, _Device(device)
			, _Address(address)

		{
			_ModbusDriver = miDriver::ModbusDriver::GetInstance(_Device);
			setupChannels(32);
		}

		void A1(bool val);
		void A2(bool val);
		void A3(bool val);
		void A4(bool val);
		void A5(bool val);
		void A6(bool val);
		void A7(bool val);
		void A8(bool val);
		void A9(bool val);
		void A10(bool val);
		void A11(bool val);
		void A12(bool val);
		void A13(bool val);
		void A14(bool val);
		void A15(bool val);
		void A16(bool val);
		void A17(bool val);
		void A18(bool val);
		void A19(bool val);
		void A20(bool val);
		void A21(bool val);
		void A22(bool val);
		void A23(bool val);
		void A24(bool val);
		void A25(bool val);
		void A26(bool val);
		void A27(bool val);
		void A28(bool val);
		void A29(bool val);
		void A30(bool val);
		void A31(bool val);
		void A32(bool val);


	};
}