#include "USensorTemperature.h"

USensorTemperature::USensorTemperature(int a_id, int a_pin, int a_timeBetweenReads, char* a_sensorName)
	: USensor(a_id, a_pin, a_timeBetweenReads, a_sensorName)
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

	semMailUTaskHandler.wait();
	UTaskRequest *mail = mailUTaskHandler.alloc();
	if(mail != NULL) {
		mail->taskRequestType = EVENT;
		mail->event.sensorId = m_sensorId;
		mail->event.value = (int) (temperature*10); // *10 to keep a 1 decimal precision
		mailUTaskHandler.put(mail);
	}
	semMailUTaskHandler.release();
}
