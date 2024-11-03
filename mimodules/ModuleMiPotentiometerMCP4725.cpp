#include "ModuleMiPotentiometerMCP4725.h"
#include <cmath>

void mimodule::ModuleMiPotentiometerMCP4725::getMaxDigits()
{
    _MaxDigits = _MCP4725MaxDigits / _VoltageReferenceADC * _MaxAnalogVoltageInput;
}

int32_t mimodule::ModuleMiPotentiometerMCP4725::getADCValue()
{
    uint16_t value = 0;
    if (_I2CDriver.read(2, reinterpret_cast<unsigned char*>( & value)) != miDriver::DriverResults::Ok)
    {
        printf("read adc value failed\n");
        return 0;
    }
    return static_cast<int32_t>(value);
}
