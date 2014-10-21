#include "USensorTemperature.h"

USensorTemperature::USensorTemperature(UDevice* device, int a_pin, int a_timeBetweenReads)
	: USensor(device, a_pin, a_timeBetweenReads)
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
		mail->event.sensorId = Device->DeviceID;
		mail->event.value = (int) (temperature*10); // *10 to keep a 1 decimal precision
		mailUTaskHandler.put(mail);
	}
	semMailUTaskHandler.release();
}
