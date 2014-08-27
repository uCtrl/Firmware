#include "USensorTemperature.h"

USensorTemperature::USensorTemperature(int a_id, int a_pin, int a_timeBetweenReads)
	: USensor(a_id, a_pin, a_timeBetweenReads)
{
	//Empty contructor
}

USensorTemperature::~USensorTemperature()
{
	//Empty destructor
}

void USensorTemperature::Read() {

	int val = ReadValue();
	double temperature = (val * 0.0053) - 50.124;

	//m_messageHandler->ReadValueFromSensor(m_sensorId, (int) temperature);
}
