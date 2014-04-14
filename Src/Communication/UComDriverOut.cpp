/*
* UComDriverOut.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "UComDriverOut.h"

Mail<UComDriverOutMailType, 2> comDriverOutMail;

/*
 * Constructor
 * */
UComDriverOut::UComDriverOut() : m_uart(USBTX, USBRX), led(LED_RED)
{
	m_uart.baud(9600);
}

/*
 * Starting thread
 * @return void
 * */
void UComDriverOut::start()
{
	char c;
	while(true)
	{
		osEvent evt = comDriverOutMail.get();
		if (evt.status == osEventMail)
		{
			led = !led;
			UComDriverOutMailType *mail = (UComDriverOutMailType*)evt.value.p;
			m_uart.puts(mail->msg);
			comDriverOutMail.free(mail);
		}
	}
}

/*
 * Destructor
 * */
UComDriverOut::~UComDriverOut()
{
}
