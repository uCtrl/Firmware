/*
 * UController.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: uctrl
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
	char c = '!';
	while(true)
	{
		Thread::wait(5000);
		m_activityLed = !m_activityLed;
		//c = m_pcSerial.getc();
		Thread::wait(700);
	}
}
