#include "ModuleMiPotentiometerADS115.h"
#include <cmath>

int16_t mimodule::ModuleMiPotentiometerADS1115::StartConversation()
{
    uint8_t wbuff[3] = { 0 };
    uint8_t rbuff[2] = { 0 };
    // set config register and start conversion
   // ANC1 and GND, 4.096v, 128s/s

    wbuff[0] = 1;    // config register is 1
    wbuff[1] = 0b11000101; // bit 15-8 0xD3

    // bit 15 flag bit for single shot
    // Bits 14-12 input selection:
    // 100 ANC0; 101 ANC1; 110 ANC2; 111 ANC3
    // Bits 11-9 Amp gain. Default to 010 here 001 P19
    // Bit 8 Operational mode of the ADS1115.
    // 0 : Continuous conversion mode
    // 1 : Power-down single-shot mode (default)

    wbuff[2] = 0b10000101; // bits 7-0  0x85

    // Bits 7-5 data rate default to 100 for 128SPS
    // Bits 4-0  comparator functions see spec sheet.

    if (_I2CDriver.write(3, wbuff) != miDriver::DriverResults::Ok)
    {
        printf("%s i2c failed\n", __func__);
        return 0;
    }

    // wait for conversion complete
    // checking bit 15
    do {
        if(_I2CDriver.read(2, wbuff) != miDriver::DriverResults::Ok)
        {
            printf("Read conversion failed\n");
            return 0;
        }
    } while ((wbuff[0] & 0x80) == 0);

    rbuff[0] = 0;   // conversion register is 0
    if (_I2CDriver.write( 1,rbuff) != miDriver::DriverResults::Ok) {
        printf("Read conversion failed\n");
        return 0;
    }

    // read 2 bytes
    if (_I2CDriver.read(2, rbuff) != miDriver::DriverResults::Ok)
    {
        printf("Read conversion failed\n");
        return 0;
    }

    // convert display results
    return rbuff[0] << 8 | rbuff[1];
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometerADS1115::init()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometerADS1115::deinit()
{
    return ModuleResult();
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometerADS1115::open()
{
    if (_I2CDriver.open() != miDriver::DriverResults::Ok)
    {
        return ModuleResult::ErrorInit;
    }
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometerADS1115::close()
{
    _I2CDriver.close();
    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometerADS1115::readInputs()
{
    int16_t val = StartConversation();
    _InputBuffer.setValue<int16_t>(val,0);
    if (_LastInputBuffer != _InputBuffer)
    {
        std::vector<mimodule::ModuleChannel*>::iterator iter;
        for (iter = _Channels.begin(); iter < _Channels.end(); ++iter)
        {
            int16_t val = _InputBuffer.getValue<int16_t>((*iter)->bitOffset());
            int16_t valLast = _LastInputBuffer.getValue<int16_t>((*iter)->bitOffset());
            int32_t val32 = (int32_t)val;
            int32_t lastVal32 = (int32_t)valLast;
            int32_t absVal = std::abs((lastVal32 - val32));


            if (absVal > (int32_t)_Filter)
            {
                val >> (*iter)->value();
                if ((*iter)->valueChangedEvent() != nullptr)
                {
                    (*iter)->valueChangedEvent()->ValueChanged((*iter)->value(), (*iter)->id());
                }
            }
        }
    }
    _InputBuffer.cpyTo(_LastInputBuffer);


    return ModuleResult::Ok;
}

mimodule::ModuleResult mimodule::ModuleMiPotentiometerADS1115::writeOutputs()
{
    return ModuleResult::Ok;
}

uint16_t mimodule::ModuleMiPotentiometerADS1115::value()
{
    return _InputBuffer.getValue<uint16_t>(0);
}
