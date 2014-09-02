#include "USensorTemperature.h"

USensorTemperature::USensorTemperature(uint32_t a_id, uint32_t a_pin, uint32_t a_timeBetweenReads, char* a_sensorName)
	: USensor(a_id, a_pin, a_timeBetweenReads, a_sensorName)
{
	//Empty contructor
}

USensorTemperature::~USensorTemperature()
{
	//Empty destructor
}

void USensorTemperature::Read() {

	uint32_t val = ReadValue();
	double temperature = (val * 0.0053) - 50.124;

	//m_messageHandler->ReadValueFromSensor(m_sensorId, (int) temperature);
}
