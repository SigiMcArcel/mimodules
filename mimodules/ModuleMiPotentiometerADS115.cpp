#include "ModuleMiPotentiometerADS115.h"
#include <cmath>

uint8_t  mimodule::ModuleMiPotentiometerADS1115::getGain(double gainAsVoltage )
{
    //search next bigger
    for (int i = static_cast<int>(ADS1115Gains::GainMax) -1; i > -1; i--)
    {
        if (gainAsVoltage <= GainRanges[i])
        {
            return static_cast<uint8_t>(i);
        }
    }
    return 0;
}

void mimodule::ModuleMiPotentiometerADS1115::getMaxDigits()
{
    
    _MaxDigits = _ADS115MaxDigits / GainRanges[_Gain] * _MaxAnalogVoltageInput;
    fprintf(stderr, "getMaxDigits _MaxDigits %f _ADS115MaxDigits %f Gain %f _MaxAnalogVoltageInput %f\n"
        , _MaxDigits
        , _ADS115MaxDigits
        , GainRanges[_Gain]
        , _MaxAnalogVoltageInput);
 
}

int32_t mimodule::ModuleMiPotentiometerADS1115::getADCValue()
{
    ADS1115Config config;
    uint8_t wbuff[3] = { 0 };
    uint8_t rbuff[2] = { 0 };
    int16_t val = 0;

    config.data[0] = 0;
    config.data[1] = 0;

    config.Reg.COMP_QUE = 1;
    config.Reg.COMP_LAT = 1;
    config.Reg.COMP_POL = 0;
    config.Reg.COMP_MODE = 0;
    config.Reg.DR = (uint8_t)ADS1115DataRate::SPS128;

    config.Reg.MODE = (uint8_t)ADS1115ConversionMod::SingleShot;
    config.Reg.PGA = (uint8_t)_Gain;
    config.Reg.MUX = 0b100;
    config.Reg.OS = 1;

    wbuff[0] = 1;
    wbuff[1] = config.data[1];
    wbuff[2] = config.data[0];

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
    int16_t tmpLow = static_cast<int16_t>(rbuff[1]);
    int16_t tmpHigh = static_cast<int16_t>(rbuff[0]);

    val = (tmpHigh << 8) | tmpLow;
    
    return val;
}
