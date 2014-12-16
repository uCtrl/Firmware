#include "USensorLight.h"

#include "UTaskHandler.h"
extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER> mailUTaskHandler;
extern Serial usbSerial;

USensorLight::USensorLight(UDevice* device, int a_pin, int a_timeBetweenReads)
	: USensor(device, a_pin, a_timeBetweenReads),
      analogIn(UPinUtils::sensorsLayout[a_pin])
{
}

USensorLight::~USensorLight()
{
	//Empty destructor
}

int USensorLight::ReadValue()
{
	return analogIn.read_u16();	
}

// This method is called periodically depending on timeBetween reads
void USensorLight::Read() 
{
	int val = ReadValue();
	
	// We set the max brightness to 450. It's about the normal lighting for a room.
	if(val > 450)
		val = 450;
	
	double lightPercentage = (double) val / 450.0 * 100;
	//double lightPercentage = (1.0 - ((double) val / 65535.0)) * 100.0;
	
	//usbSerial.printf("Light percentage : %2f \r\n", lightPercentage);
	Device->CurrentValue = lightPercentage;

	semMailUTaskHandler.wait();
	UTaskRequest *mail = mailUTaskHandler.alloc();
	if(mail != NULL) {
		mail->taskRequestType = EVENT;
		mail->event.sensorId = Device->DeviceID;
		mail->event.value = lightPercentage;
		mailUTaskHandler.put(mail);
	}
}

