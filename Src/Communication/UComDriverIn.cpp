/*
* UComDriverIn.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "UComDriverIn.h"

/*
 * Constructor
 * */
UComDriverIn::UComDriverIn() : m_uart(USBTX, USBRX), led(LED_GREEN)
{
	m_rxCount = 0;
	m_uart.baud(9600);
}

/*
 * Reset the serial buffer.
 * @return void
 * */
void UComDriverIn::resetBuffer()
{
    m_rxCount = 0;
}

/*
 * Starting thread
 * @return void
 * */
void UComDriverIn::start()
{
	led = true;
	char c;
	while(true)
	{
		c = m_uart.getc();
		led = !led;	//Green led flashing on character input (for debugging)
		// EOT 0x04 (End Of Transmission) || 0x13 Enter Key (for debugging)
		if(c == 4 || c == 13)
		{
			m_rxBuffer[m_rxCount] = '\0';
			m_rxCount++;
			handleMsg();
			resetBuffer();
		}
		else
		{
			m_rxBuffer[m_rxCount] = c;
			m_rxCount++;

			if(m_rxCount >= UCOMIN_BUFFER_SIZE - 1)
			{
				m_rxBuffer[m_rxCount] = '\0';
				m_rxCount++;
				handleMsg();
				resetBuffer();
			}
		}
	}
}

/*
 * Handle messages comming from serial.
 * Push messages to UMsgHandler thread.
 * @return void
 * */
void UComDriverIn::handleMsg()
{
	UMsgHandlerMailType *mail = msgHandlerMail.alloc();
	mail->id3 = 1;
	strcpy(mail->msg, m_rxBuffer);
	msgHandlerMail.put(mail);
	//m_uart.puts(m_rxBuffer);
}

/*
 * Destructor
 * */
UComDriverIn::~UComDriverIn()
{
}
