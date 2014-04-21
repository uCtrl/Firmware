#include "USensorLight.h"

USensorLight::USensorLight(FakeMessageHandler* messageHandler, char* a_name, int a_pin, int timeBetweenReads)
	: USensor(messageHandler, a_name, timeBetweenReads)
{
	m_lightSensorCount = 0;
}

void USensorLight::Read() {

	m_lightSensorBuffer[m_lightSensorCount] = ReadValue();

	int sum = 0;
	for(int i = 0; i < 10; i++) {
		sum += m_lightSensorBuffer[i];
	}

	int val = sum/10;

	m_lightSensorCount++;

	if(m_lightSensorCount >= 10)
		m_lightSensorCount = 0;

	m_messageHandler->ReadValueFromSensor(m_sensorName, val);
}
