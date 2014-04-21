#include "USensorTemperature.h"

USensorTemperature::USensorTemperature(FakeMessageHandler* messageHandler, char* a_name, int a_pin, int timeBetweenReads)
	: USensor(messageHandler, a_name, timeBetweenReads)
{
	//Empty contructor
}

void USensorTemperature::Read() {

	int val = ReadValue();
	double temperature = (val * 0.0053) - 50.124;

	m_messageHandler->ReadValueFromSensor(m_sensorName, (int) temperature);
}
