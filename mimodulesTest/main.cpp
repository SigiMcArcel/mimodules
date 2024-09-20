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
        printf("GeconEvents ValueChanged % s value = %d\n", id.c_str(), val);
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

int main()
{
    bool blink = false;
    int segVal = 0;
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
        std::string Id("E");
        Id.append(std::to_string(i));
        geconIn1.getChannel(Id)->registerChannelEvent(_GeconEvents1);
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
        /*for (int i = 1; i < 32; i++)
        {
            std::string Id("A");
            Id.append(std::to_string(i));
            mimodule::ModuleChannel* c = geconOut3.getChannel(Id);
            mimodule::ModuleChannel* c2 = geconOut4.getChannel(Id);
            if(c != nullptr)
            {
                blink >> c->value();
                blink >> c2->value();
            }
        }*/
        mimodule::ModuleChannel* c = geconOut3.getChannel("A31");
        mimodule::ModuleChannel* c2 = geconOut4.getChannel("A31");
        if ((c != nullptr) && (c2 != nullptr))
        {
            blink >> c->value();
            blink >> c2->value();
        }
        else
        {
            printf("huch");
        }
        blink = !blink;

        mimodule::ModuleChannel* seven1 = sevenofnine.getChannel("Segment1");
        mimodule::ModuleChannel* seven2 = sevenofnine.getChannel("Segment2");
        mimodule::ModuleChannel* seven3 = sevenofnine.getChannel("Segment3");
        mimodule::ModuleChannel* seven4 = sevenofnine.getChannel("Segment4");
        mimodule::ModuleChannel* seven5 = sevenofnine.getChannel("Segment5");
        mimodule::ModuleChannel* seven6 = sevenofnine.getChannel("Segment6");
        mimodule::ModuleChannel* seven7 = sevenofnine.getChannel("Segment7");
        mimodule::ModuleChannel* seven8 = sevenofnine.getChannel("Segment8");
        
        segVal >> seven1->value();
        segVal >> seven2->value();
        segVal >> seven3->value();
        segVal >> seven4->value();
        segVal >> seven5->value();
        segVal >> seven6->value();
        segVal >> seven7->value();
        segVal >> seven8->value();
        segVal++;
        if (segVal > 9)
        {
            segVal = 0;
        }
        ::sleep(1);
    }
    return 0;




}



#ifdef TESTHOERTER




class HoerterEvents :public mimodule::ModuleValueChangedEvent
{
    mimodule::ModuleHoerterOutput _Output;

public:
    HoerterEvents(const mimodule::ModuleHoerterOutput& output)
        :_Output(output)
    {

    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {
        
        bool val = false;
        val << value;

        _Output.A1(val);
        printf("ValueChanged Modul 1 E1 % s value = %d\n", id.c_str(),val);
    }
   
};
class HoerterEvents1 :public mimodule::ModuleValueChangedEvent
{
    mimodule::ModuleHoerterOutput _Output;

public:
    HoerterEvents1(const mimodule::ModuleHoerterOutput& output)
        :_Output(output)
    {

    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {
        bool val = false;
        val << value;
        _Output.A2(val);
        printf("ValueChanged Modul 1 E2 % s value = %d\n", id.c_str(), val);
    }
   
};
class HoerterEvents2 :public mimodule::ModuleValueChangedEvent
{
    mimodule::ModuleHoerterOutput _Output;

public:
    HoerterEvents2(const mimodule::ModuleHoerterOutput& output)
        :_Output(output)
    {
        
    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {
        bool val = false;
        val << value;
        _Output.A6(val);
        printf("ValueChanged Modul 2 E1 % s value = %d\n", id.c_str(), val);
    }
  
};

class HoerterEventsPot :public mimodule::ModuleValueChangedEvent
{
   
public:
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {

        uint16_t val = 0;
        val << value;

        
        printf("ValueChanged Modul Pot % s value = %d\n", id.c_str(), val);
    }

};


int main()
{
    mimodule::ModuleHoerterOutput Module4(0x20,"Module4");
    mimodule::ModuleHoerterOutput Module5(0x21, "Module5");
    mimodule::ModuleHoerterOutput Module6(0x22, "Module6");

    HoerterEvents* events = new HoerterEvents(Module4);
    HoerterEvents1* events1 = new HoerterEvents1(Module4);
    HoerterEvents2* events2 = new HoerterEvents2(Module6);
    HoerterEventsPot* eventsPot = new HoerterEventsPot();

    mimodule::ModuleHoerterInput Module1(0x38, "Module1");
    mimodule::ModuleHoerterInput Module2(0x39, "Module2");
    mimodule::ModuleHoerterInput Module3(0x3A, "Module3");
    mimodule::ModuleMiPotentiometer ModulePot(0x42,3, "ModulePot");

    Module6.A1(true);
    Module6.A2(true);



   
   


    Module1.getChannel("E1")->registerChannelEvent(events);
    Module1.getChannel("E2")->registerChannelEvent(events1);
    Module2.getChannel("E1")->registerChannelEvent(events2);
    ModulePot.getChannel("Potentiometer")->registerChannelEvent(eventsPot);
    

    mimodule::ModuleManager man(20);
    man.addModule(&Module1);
    man.addModule(&Module2);
    man.addModule(&Module3);
    man.addModule(&Module4);
    man.addModule(&Module5);
    man.addModule(&Module6);
    man.addModule(&ModulePot);
    man.start();

    while (1)
    {
        ::sleep(1);
    }
    return 0;
}
#endif // TESTHOERTER