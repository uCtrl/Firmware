#include "FakeActuator.h"

// Constructor
FakeActuator::FakeActuator()
: digitalOut(UPinUtils::leds[0])
{
}

FakeActuator::FakeActuator(UDevice* device, int a_pin)
: digitalOut(UPinUtils::leds[a_pin])
{
    Device = device;
}

// Save the current state of the sensor.
void FakeActuator::SetValue(int a_value)
{
	printf("Setting value to %d\r\n", a_value);
    digitalOut = a_value;
}
