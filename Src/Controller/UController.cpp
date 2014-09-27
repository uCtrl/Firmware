/*
 * UController.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: uctrl
 */

#include "UController.h"
#ifdef TARGET_LPC1768
#define LED_BLUE LED3
#endif

UController::UController():m_activityLed(LED_BLUE),m_pcSerial(USBTX,USBRX)
{
}

UController::~UController()
{
}

void UController::start()
{
	for(;;)
	{
		Thread::wait(5000);
		m_activityLed = !m_activityLed;
	}
}
