#include "USensorLight.h"

USensorLight::USensorLight(FakeMessageHandler* a_messageHandler, int a_id, int a_pin, int a_timeBetweenReads)
	: USensor(a_messageHandler, a_id, a_pin, a_timeBetweenReads)
{
	m_lightSensorCount = 0;
}

USensorLight::~USensorLight()
	: ~USensor()
{
	//Empty destructor
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

	m_messageHandler->ReadValueFromSensor(m_sensorId, val);
}
