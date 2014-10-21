#include "USensorLight.h"

USensorLight::USensorLight(UDevice* device, int a_pin, int a_timeBetweenReads)
	: USensor(device, a_pin, a_timeBetweenReads),
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

	int sum = 0;
	for(int i = 0; i < 10; i++) {
		sum += m_lightSensorBuffer[i];
	}

	int val = sum/10;

	m_lightSensorCount++;

	if(m_lightSensorCount >= 10)
		m_lightSensorCount = 0;

	semMailUTaskHandler.wait();
	UTaskRequest *mail = mailUTaskHandler.alloc();
	if(mail != NULL) {
		mail->taskRequestType = EVENT;
		mail->event.sensorId = Device->DeviceID;
		mail->event.value = val;
		mailUTaskHandler.put(mail);
	}
	semMailUTaskHandler.release();
}
