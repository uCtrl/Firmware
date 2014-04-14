/*
* UController.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
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
<<<<<<< HEAD
	//char c = '!';
	while(true)
	{
		Thread::wait(3000);
		m_activityLed = false;
		Thread::wait(200);
		m_activityLed = true;
		//c = m_pcSerial.getc();
		//m_pcSerial.putc(c);
=======
	for(;;)
	{
		Thread::wait(5000);
		m_activityLed = !m_activityLed;
>>>>>>> f162662eaa6326c9bab8e4250162f27e6d4cd9fc
	}
}
