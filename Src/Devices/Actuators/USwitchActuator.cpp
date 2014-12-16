#include "USwitchActuator.h"

extern Serial usbSerial;

// Constructor
USwitchActuator::USwitchActuator()
: UActuator(),
  digitalOut(UPinUtils::actuatorsLayout[0])
{
}

USwitchActuator::USwitchActuator(UDevice* device, int a_pin)
: UActuator(device),
  digitalOut(UPinUtils::actuatorsLayout[a_pin])
{
    digitalOut = atoi(device->Value.c_str());
}

void USwitchActuator::SetValue(string a_value)
{
    Device->Value = a_value;
    digitalOut = atoi(a_value.c_str());
#ifdef MINIMALIST_PRINT
    usbSerial.printf("Device %d digitalOut set to %s\r\n", Device->DeviceID, a_value.c_str());
#endif
}

