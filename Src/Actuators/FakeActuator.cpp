#include "FakeActuator.h"

// Constructor
FakeActuator::FakeActuator() : digitalOut(UPinUtils::digitalInOut[0])
{
}

FakeActuator::FakeActuator(int a_id, int a_pin) : digitalOut(UPinUtils::digitalInOut[a_pin])
{
    m_actuatorId = a_id;
}

// Save the current state of the sensor.
void FakeActuator::SetValue(int a_value)
{
    digitalOut = a_value;
}
