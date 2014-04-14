/*
* UController.h
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/


#ifndef UCONTROLLER_H_
#define UCONTROLLER_H_
#include "mbed.h"
#include "rtos.h"
typedef enum {
    MESSAGE = 0x0,
    ADD_SENSOR = 0x1,
    DELETE_SENSOR = 0x2,
} messageType;
class UController
{
private:
	DigitalOut m_activityLed;
	Serial m_pcSerial;

	void printf(char* str, uint16_t len);
public:
	UController();
	~UController();

	void start();
};

#endif /* UCONTROLLER_H_ */
