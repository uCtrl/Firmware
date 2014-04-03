#include "FakeActuator.h"

// Constructor
FakeActuator::FakeActuator() : digitalOut(UPinUtils::digitalInOut[0])
{
}

FakeActuator::FakeActuator(char* a_name, int a_pin) : digitalOut(UPinUtils::digitalInOut[a_pin])
{
    m_actuatorName = a_name;
}

// Save the current state of the sensor.
void FakeActuator::SetValue(int a_value)
{
    digitalOut = a_value;
}
