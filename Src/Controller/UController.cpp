/*
* UController.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "UController.h"

UController::UController():m_activityLed(LED_BLUE),m_pcSerial(USBTX,USBRX)
{
}

UController::~UController()
{
}

void UController::start()
{
	//char c = '!';
	while(true)
	{
		Thread::wait(3000);
		m_activityLed = false;
		Thread::wait(200);
		m_activityLed = true;
		//c = m_pcSerial.getc();
		//m_pcSerial.putc(c);
	}
}
