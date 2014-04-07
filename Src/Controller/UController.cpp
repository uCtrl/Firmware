/*
 * UController.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: uctrl
 */

#include "UController.h"

UController::UController():m_activityLed(LED_BLUE)
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
