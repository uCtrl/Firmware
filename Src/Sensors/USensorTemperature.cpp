#include "USensorTemperature.h"

USensorTemperature::USensorTemperature(FakeMessageHandler* a_messageHandler, int a_id, int a_pin, int a_timeBetweenReads)
	: USensor(a_messageHandler, a_id, a_pin, a_timeBetweenReads)
{
	//Empty contructor
}

USensorTemperature::~USensorTemperature()
	: ~USensor()
{
	//Empty destructor
}

void USensorTemperature::Read() {

	int val = ReadValue();
	double temperature = (val * 0.0053) - 50.124;

	m_messageHandler->ReadValueFromSensor(m_sensorId, (int) temperature);
}
