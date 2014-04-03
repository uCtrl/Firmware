#include "FakeSensor.h"

// Constructor
FakeSensor::FakeSensor() : analogIn(UPinUtils::analogIn[0])
{
}

FakeSensor::FakeSensor(char* a_name, int a_pin) : analogIn(UPinUtils::analogIn[a_pin])
{
    m_sensorName = a_name;
    ticker.attach(this, &FakeSensor::Read, 5.0);
}


// Forcefully reads a new value from the sensor, saves it in m_LastValueRead
// and raises the m_NewValueAvailableFlag.
void FakeSensor::ForceNewValueRead()
{

}

// Save the current state of the sensor.
void FakeSensor::SaveState()
{

}

void FakeSensor::Read()
{
	int val = analogIn.read_u16();

    FakeMessageHandler::GetInstance()->ReadValueFromSensor(m_sensorName, val);
}
