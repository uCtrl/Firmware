#include "FakeActuator.h"

// Constructor
FakeActuator::FakeActuator()
: UDevice(),
  digitalOut(UPinUtils::digitalInOut[0])
{
    m_actuatorId = 0;
    m_actuatorName = "";
}

FakeActuator::FakeActuator(int a_id, int a_pin, char* a_deviceName)
: UDevice(a_id, a_deviceName),
  digitalOut(UPinUtils::digitalInOut[a_pin])
{
    m_actuatorId = a_id;
    m_actuatorName = a_deviceName;
}

// Save the current state of the sensor.
void FakeActuator::SetValue(int a_value)
{
    digitalOut = a_value;
}
