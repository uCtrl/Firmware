#include "USensorLight.h"

USensorLight::USensorLight(uint32_t a_id, uint32_t a_pin, uint32_t a_timeBetweenReads, char* a_sensorName)
	: USensor(a_id, a_pin, a_timeBetweenReads, a_sensorName),
	  m_lightSensorBuffer{0}
{
	m_lightSensorCount = 0;
}

USensorLight::~USensorLight()
{
	//Empty destructor
}

void USensorLight::Read() {

	m_lightSensorBuffer[m_lightSensorCount] = ReadValue();

	uint32_t sum = 0;
	for(uint32_t i = 0; i < 10; i++) {
		sum += m_lightSensorBuffer[i];
	}

	uint32_t val = sum/10;

	m_lightSensorCount++;

	if(m_lightSensorCount >= 10)
		m_lightSensorCount = 0;

	semMailUTaskHandler.wait();
	UTaskRequest *mail = mailUTaskHandler.alloc();
	if(mail != NULL) {
		mail->taskRequestType = EVENT;
		mail->event.sensorId = m_sensorId;
		mail->event.value = val;
		mailUTaskHandler.put(mail);
		printf("Sent event from sensor %lu\n\r", mail->event.sensorId);
	}
}
