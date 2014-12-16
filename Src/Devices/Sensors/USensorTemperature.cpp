#include "USensorTemperature.h"

extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER> mailUTaskHandler;

extern Serial usbSerial;

USensorTemperature::USensorTemperature(UDevice* device, int a_pin, int a_timeBetweenReads)
	: USensor(device, a_pin, a_timeBetweenReads),
	  analogIn(UPinUtils::sensorsLayout[a_pin])
{
	//Empty contructor
}

USensorTemperature::~USensorTemperature()
{
	//Empty destructor
}

void USensorTemperature::Read() 
{	
	double val = (double)analogIn;
     
    double temperature = (val*3.1-0.46)*100;
    
	//usbSerial.printf("Temperature : %f \r\n", temperature);
	
	semMailUTaskHandler.wait();
	UTaskRequest *mail = mailUTaskHandler.alloc();
	if(mail != NULL) {
		mail->taskRequestType = EVENT;
		mail->event.sensorId = Device->DeviceID;
		mail->event.value = temperature; // *10 to keep a 1 decimal precision
		mailUTaskHandler.put(mail);
	}
}

