
#include "UActuator.h"

extern Serial usbSerial;

// Constructor
UActuator::UActuator()
{
}

UActuator::UActuator(UDevice* device)
{
    Device = device;
}

UActuator::~UActuator()
{
    delete Device;
}

void UActuator::SetValue(string a_value)
{
}

