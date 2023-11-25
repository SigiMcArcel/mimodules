#include <cstdio>
#include <mi/mimodules/ModuleHoerterInput.h>
#include <mi/mimodules/ModuleHoerterOutput.h>
#include <mi/mimodules/ModuleMiPotentiometer.h>
#include <mi/mimodules/ModuleManager.h>
#include <mi/mimodules/ModuleInterface.h>
#include <mi/mimodules/ModulePointer.h>
#include <mi/mimodules/ModuleMidiInput.h>
#include <mi/mimodules/ModuleMidiOutput.h>
#include <iostream>
#include <typeinfo>

#define PRINT_NAME(x) std::cout << #x << " - " << typeid(x).name() << '\n'

class MidiEvents :public mimodule::ModuleValueChangedEvent
{
public:
    MidiEvents()
    {

    }
    // Geerbt über ModuleValueChangedEvent
    virtual void ValueChanged(mimodule::ModuleValue& value, const std::string& id) override
    {
        bool val = false;
        val << value;
        printf("ValueChanged % s value = %d\n", id.c_str(), val);
    }

};

int main()
{
    mimodule::ModuleMidiInput input(0, "Inputs");
    mimodule::ModuleMidiOutput output0(0, "Ouputs0");
    mimodule::ModuleMidiOutput output1(1, "Ouputs1");
    bool blink = false;

    MidiEvents* events = new MidiEvents();
    for (int i = 1; i < 65; i++)
    {
        std::string Id("E");
        Id.append(std::to_string(i));
        input.getChannel(Id)->registerChannelEvent(events);
    }

    mimodule::ModuleManager man(20);
    man.addModule(&input);
    man.addModule(&output0);
    man.addModule(&output1);
    man.start();

    while (1)
    {
        for (int i = 1; i < 65; i++)
        {
            std::string Id("A");
            Id.append(std::to_string(i));
            mimodule::ModuleChannel* c = output0.getChannel(Id);
            if(c != nullptr)
            {
                blink >> c->value();
            }
        }
        blink = !blink;
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