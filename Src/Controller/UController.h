/*
 * UController.h
 *
 *  Created on: Mar 23, 2014
 *      Author: uctrl
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

/** @Deprecated: UTaskCfg class is used s a thread manager*/
class UController
{
private:
	Serial m_pcSerial;
	DigitalOut m_activityLed;
public:
	UController();
	~UController();

	/** start the content of thread */
	void start();
};

#endif /* UCONTROLLER_H_ */
