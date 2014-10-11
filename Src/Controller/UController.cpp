/*
* UController.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
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
		Thread::wait(3000);
		m_activityLed = false;
		Thread::wait(200);
		m_activityLed = true;
	}
}
