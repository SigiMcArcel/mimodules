#include "ModuleMiRpiGpio.h"

void mimodule::ModuleMiRpiGpio::setupGpioPin(mimodule::ModuleMiRpiGpioState state, mimodule::ModulChannelDirection dir, int pinNumber)
{
	mimodule::ModuleMiRpiGpioConfiguration conf;
	conf.Size = sizeof(mimodule::ModuleMiRpiGpioConfiguration);
	conf.State = state;
	conf.Dir = dir;
	conf.Number = pinNumber;
	std::string name("GPIO");
	name.append(std::to_string(pinNumber));
	_Channels.push_back(new ModuleChannel(name, ModulValueType::Boolean, 0, conf.Dir, reinterpret_cast<ModuleChannelParameter*>(&conf)));
}

void mimodule::ModuleMiRpiGpio::setup()
{
	//Setting all alternative used pins to inactive
	// 3.3V
	//Gpio 2, alt sda, connector pin 3
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 2);
	//Gpio 3, alt scl, connector pin 7
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 3);
	//Gpio 4, alt gpioclk0, connector pin 9
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 4);
	//GND
	//Gpio 17, alt none, connector pin 11
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 17);
	//Gpio 27, alt none, connector pin 13
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 27);
	//Gpio 22, alt none, connector pin 15
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 22);
	// 3.3V
	//Gpio 10, alt MOSI, connector pin 19
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 10);
	//Gpio 9, alt MISO, connector pin 21
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 9);
	//Gpio 11, alt SCLK, connector pin 23
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 11);
	//GND
	//ID_SD
	//Gpio 5, alt none, connector pin 29
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 5);
	//Gpio 6, alt none, connector pin 31
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 6);
	//Gpio 13, alt none, connector pin 33
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 13);
	//Gpio 19, alt none, connector pin 35
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 19);
	//Gpio 26, alt none, connector pin 37
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 26);
	//GND

	//second row 
	//5V
	//5V
	//GND
	//Gpio 14, alt TXD, connector pin 2
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 14);
	//Gpio 15, alt RXD, connector pin 4
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 5);
	//Gpio 18, alt none, connector pin 12
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 18);
	//GND
	//Gpio 23, alt none, connector pin 16
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 23);
	//Gpio 24, alt none, connector pin 18
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 24);
	//GND
	//Gpio 25, alt none, connector pin22
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 25);
	//Gpio 8, alt CE0, connector pin 24
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 8);
	//Gpio 7, alt CE1, connector pin 26
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Inactive, mimodule::ModulChannelDirection::Input, 7);
	//ID_SC
	//Gpio 12, alt none, connector pin 32
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 12);
	//GND
	//Gpio 16, alt none, connector pin 36
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 16);
	//Gpio 20, alt none, connector pin 38
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 20);
	//Gpio 21, alt none, connector pin 40
	setupGpioPin(mimodule::ModuleMiRpiGpioState::Free, mimodule::ModulChannelDirection::Input, 21);
}

mimodule::ModuleMiRpiGpioConfiguration* mimodule::ModuleMiRpiGpio::findGPIO(std::vector<ModuleMiRpiGpioConfiguration>& condiguration, int number)
{
	std::vector<mimodule::ModuleMiRpiGpioConfiguration>::iterator iter;
	for (iter = condiguration.begin(); iter < condiguration.end(); ++iter)
	{
		if (number == (*iter).Number)
		{
			return iter.base();
		}
	}
	return nullptr;
}

void mimodule::ModuleMiRpiGpio::configure(std::vector<ModuleMiRpiGpioConfiguration>& condiguration)
{
	std::vector<mimodule::ModuleChannel*>::iterator iter;
	for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
	{
		ModuleMiRpiGpioConfiguration* defaultConf = reinterpret_cast<ModuleMiRpiGpioConfiguration*>((*iter)->parameter());
		if (defaultConf != nullptr)
		{
			ModuleMiRpiGpioConfiguration* actconf = findGPIO(condiguration, defaultConf->Number);
			if (actconf != nullptr)
			{
				if (defaultConf->State == ModuleMiRpiGpioState::Free)
				{
					defaultConf->Dir = actconf->Dir;
					defaultConf->State = ModuleMiRpiGpioState::Active;
				}
				else
				{
					printf("%s GPIO%d is used or alternate\n", __func__, defaultConf->Number);
				}
			}
		}
	}
	//Configure HW
	for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
	{
		ModuleMiRpiGpioConfiguration* conf = reinterpret_cast<ModuleMiRpiGpioConfiguration*>((*iter)->parameter());
		if (conf != nullptr)
		{
			if (conf->State == ModuleMiRpiGpioState::Active)
			{
				_GPIODriver.GpioEnable(conf->Number, true);
				_GPIODriver.GpioSetDirection(conf->Number, static_cast<miDriver::GPIODirection>(conf->Dir));
			}
		}
	}
}

mimodule::ModuleResult mimodule::ModuleMiRpiGpio::init()
{
	return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiRpiGpio::deinit()
{
	return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiRpiGpio::open()
{
	ModuleBase::open();
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiRpiGpio::close()
{
	ModuleBase::close();
	return ModuleResult::Ok;
}

void mimodule::ModuleMiRpiGpio::ValueChanged(mimodule::ModuleValue& value, const std::string& id)
{
	ModuleChannel* channel = getChannel(id);
	if (channel == nullptr)
	{
		return;
	}

	ModuleMiRpiGpioConfiguration* conf = reinterpret_cast<ModuleMiRpiGpioConfiguration*>(channel->parameter());
	if (conf != nullptr)
	{
		if (conf->State == ModuleMiRpiGpioState::Active && conf->Dir == ModulChannelDirection::Output)
		{
			bool val = false;
			val = value.getValue<bool>();
			_GPIODriver.GpioWrite(conf->Number, val);
		}
	}
}

mimodule::ModuleResult mimodule::ModuleMiRpiGpio::readInputsPrivate(bool init)
{
	miDriver::DriverResults results = miDriver::DriverResults::Ok;
	std::vector<mimodule::ModuleChannel*>::iterator iter;

	for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
	{
		ModuleMiRpiGpioConfiguration* conf = reinterpret_cast<ModuleMiRpiGpioConfiguration*>((*iter)->parameter());
		if (conf != nullptr)
		{
			if (conf->State == ModuleMiRpiGpioState::Active && conf->Dir == ModulChannelDirection::Input)
			{
				bool val = false;
				val = _GPIODriver.GpioRead(conf->Number,&results);
				(*iter)->value().setValue<bool>(val);
			}
		}
	}
	return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiRpiGpio::writeOutputsPrivate()
{
	return ModuleResult::Ok;
}
