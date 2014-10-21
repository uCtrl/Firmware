#include "FakeActuator.h"

// Constructor
FakeActuator::FakeActuator()
: digitalOut(UPinUtils::digitalInOut[0])
{
}

FakeActuator::FakeActuator(UDevice* device, int a_pin)
: digitalOut(UPinUtils::digitalInOut[a_pin])
{
    Device = device;
}

// Save the current state of the sensor.
void FakeActuator::SetValue(int a_value)
{
    digitalOut = a_value;
}
