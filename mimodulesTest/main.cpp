#include <cstdio>
#include <mi/mimodules/ModuleHoerterInput.h>
#include <mi/mimodules/ModuleHoerterOutput.h>
#include <mi/mimodules/ModuleMiPotentiometerADS115.h>
#include <mi/mimodules/ModuleManager.h>
#include <mi/mimodules/ModuleInterface.h>
#include <mi/mimodules/ModulePointer.h>
#include <mi/mimodules/ModuleMidiInput.h>
#include <mi/mimodules/ModuleMidiOutput.h>
#include <mi/mimodules/ModuleGecon32Input.h>
#include <mi/mimodules/ModuleGecon32Output.h>
#include <mi/mimodules/ModuleMiPhoneNumber.h>
#include <mi/mimodules/ModuleMiRpiGpio.h>
#include <mi/mimodules/ModuleMiSevenSegment.h>
#include <mi/miutils/Timer.h>



#include <iostream>
#include <typeinfo>

#define PRINT_NAME(x) std::cout << #x << " - " << typeid(x).name() << '\n'

class VolumeEvents :public mimodule::ModuleValueChangedEvent
{
public:
    VolumeEvents()
    {

    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {
        double val = 0;
        val << value;
        printf(" VolumeEvents ValueChanged % s value = %f\n", id.c_str(), val);
    }

};

class GeconEvents :public mimodule::ModuleValueChangedEvent
{
public:
    GeconEvents()
    {

    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {
        bool val = false;
        val << value;
  
    }

};

class GeconEvents2 :public mimodule::ModuleValueChangedEvent
{
public:
    GeconEvents2()
    {

    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {
        bool val = false;
        val << value;
        printf("GeconEvents2 ValueChanged % s value = %d\n", id.c_str(), val);
    }

};

class PhoneNumberEvents :public mimodule::ModuleValueChangedEvent
{
public:
    PhoneNumberEvents()
    {

    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {
        bool val = false;
        val << value;
        printf("PhoneNumberEvents ValueChanged % s value = %d\n", id.c_str(), val);
    }

};

class PhoneJackEvents : public mimodule::ModuleValueChangedEvent
{
public:
    PhoneJackEvents()
    {

    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue & value, const std::string & id) override
    {
        bool val = false;
        val << value;
        printf("PhoneJackEvents ValueChanged % s value = %d\n", id.c_str(), val);
    }

};

class GPIOEvents :public mimodule::ModuleValueChangedEvent
{
public:
    GPIOEvents()
    {

    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {
        bool val = false;
        val << value;
        printf("GPIOEvents ValueChanged % s value = %d\n", id.c_str(), val);
    }

};

class Blinker :public miutils::EventListener
{
    mimodule::ModuleChannel* _Channel;
    miutils::Timer _Timer;
    bool _Toggle;
    bool _Enable;
public:
    Blinker()
        :_Channel(nullptr)
        , _Timer("Timer", this)
        , _Toggle(false)
        , _Enable(false)
    {
        _Timer.Start(250, nullptr, 10, miutils::Schedulers::Other);
    }

    void blinkstart(mimodule::ModuleChannel* channel)
    {
        _Channel = channel;
        _Enable = true;
    }
    void blinkstop()
    {
        _Enable = false;
    }
    virtual void timerEventOccured(void* sender, const std::string& name)
    {
        if (_Enable)
        {
            if (_Channel != nullptr)
            {
                if (_Toggle)
                {
                    _Toggle = false;
                }
                else
                {
                    _Toggle = true;
                }
                _Toggle >> _Channel->value();
            }
        }
        else
        {
            _Toggle = false;
            if (_Channel != nullptr)
            {
                _Toggle >> _Channel->value();
            }
        }
    }
};

int main()
{
    Blinker blink;

    mimodule::ModuleGecon32Input geconIn1("/dev/ttyUSB0", 1, "geconIn1");
    mimodule::ModuleGecon32Input geconIn2("/dev/ttyUSB0", 2, "geconIn2");
    mimodule::ModuleGecon32Output geconOut3("/dev/ttyUSB0", 3, "geconOut3");
    mimodule::ModuleGecon32Output geconOut4("/dev/ttyUSB0", 4, "geconOut4");
    mimodule::ModuleMiPhoneNumber phoneNumber(5, "phone", 17, 27);
    mimodule::ModuleMiRpiGpioConfiguration conf;
    std::vector<mimodule::ModuleMiRpiGpioConfiguration> confs;
    conf.Dir = mimodule::ModulChannelDirection::Input;
    conf.Number = 5;
    conf.State = mimodule::ModuleMiRpiGpioState::Active;
    confs.push_back(conf);
    mimodule::ModuleMiRpiGpio phoneJack("PhoneJack", confs);
    mimodule::ModuleMiSevenSegment sevenofnine("/dev/spidev0.0", "sevenofnine");
    mimodule::ModuleMiPotentiometerADS1115 ModulVolume(0x48, 0.1, "Volume");


    //setup phone nummer
    PhoneNumberEvents* _PhoneNumberEvents = new PhoneNumberEvents();
    phoneNumber.getChannel("PhoneNumber")->registerChannelEvent(_PhoneNumberEvents);
    //setup gecon
    GeconEvents* _GeconEvents1 = new GeconEvents();
    GeconEvents2* _GeconEvents2 = new GeconEvents2();
    for (int i = 0 ; i < 32 ; i++)
    {
        std::string Id("E1.");
        Id.append(std::to_string(i));
        geconIn1.getChannel(Id)->registerChannelEvent(_GeconEvents1);
        Id = "E2.";
        Id.append(std::to_string(i));
        geconIn2.getChannel(Id)->registerChannelEvent(_GeconEvents2);
        
    }

    //setup module volume
    VolumeEvents* _VolumeEvents = new VolumeEvents();
    ModulVolume.getChannel("Potentiometer")->registerChannelEvent(_VolumeEvents);

    //setup phoneJack
    GPIOEvents* _GPIOEvents = new GPIOEvents();
    phoneJack.getChannel("GPIO5")->registerChannelEvent(_GPIOEvents);

    mimodule::ModuleManager man(10);
    man.addModule(&phoneNumber);
    man.addModule(&sevenofnine);
    man.addModule(&geconIn1);
    man.addModule(&geconIn2);
    man.addModule(&geconOut3);
    man.addModule(&geconOut4);
    man.addModule(&ModulVolume);
    man.addModule(&phoneJack);
    man.addModule(&ModulVolume);
    man.start();



    while (1)
    {
        std::string input("A");
        std::string cmd;
        mimodule::ModuleChannel* c = nullptr;
        
        std::cout << "Channel >";
        std::getline(std::cin, cmd);
        input.append(cmd);
        c = geconOut3.getChannel(input);
        if (c == nullptr)
        {
            c = geconOut4.getChannel(input);
            if (c == nullptr)
            {
                printf("Channel %s not found\n", input.c_str());
                continue;
            }
        }
        printf("Channel %s\n", input.c_str());
        blink.blinkstart(c);
        std::getline(std::cin, cmd);
        blink.blinkstop();

    }
    return 0;
}
