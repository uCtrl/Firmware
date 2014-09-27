#include "FakeActuator.h"

// Constructor
FakeActuator::FakeActuator() : digitalOut(UPinUtils::digitalInOut[0])
{
    m_actuatorId = 0;
    m_actuatorName = "";
}

FakeActuator::FakeActuator(int a_id, int a_pin, char* a_actuatorName) : digitalOut(UPinUtils::digitalInOut[a_pin])
{
    m_actuatorId = a_id;
    m_actuatorName = a_actuatorName;
}

// Save the current state of the sensor.
void FakeActuator::SetValue(int a_value)
{
    digitalOut = a_value;
}
