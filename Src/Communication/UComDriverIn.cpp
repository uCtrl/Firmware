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
UComDriverIn::UComDriverIn() : m_uart(USBTX, USBRX), m_led(LED1)
{
	m_uart.baud(SERIAL_BAUD);
	m_rxCount = 0;
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
	m_led = true;
	if(USE_LWIP)
	{
		printf("\n\r - LWIP Mode - \n\r");

	    EthernetInterface eth;
	    eth.init(); //Use DHCP
	    eth.connect();
	    printf("IP Address is %s\n", eth.getIPAddress());

	    m_udpSocket.bind(UDPSOCKET_PORT);

	    printf("UDP Socket binded to port %d\n\r", UDPSOCKET_PORT);
	    while(true)
		{
			printf("Waiting for packet...\n\r");
	        m_rxCount = m_udpSocket.receiveFrom(m_udpClient, m_rxBuffer, sizeof(m_rxBuffer));
	        m_rxBuffer[m_rxCount] = '\0';
	        m_led = !m_led;	//led flashing on input
	        handleMsg();
		}
	}
	else
	{
		printf("\n\r - Serial Mode - \n\r");
		//SERIAL handle one char at the time
		char c;
		while(true)
		{
			c = m_uart.getc();
			//printf("%c", c);
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
				if(m_rxCount >= COM_BUFFER_SIZE - 1)
				{
					m_rxBuffer[m_rxCount] = '\0';
					m_rxCount++;
					handleMsg();
					resetBuffer();
				}
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
	if(USE_LWIP)
	{
		mail->endPoint = m_udpClient;
	}
	strncpy(mail->msg, m_rxBuffer, sizeof(m_rxBuffer));
	msgHandlerMail.put(mail);
}

/*
 * Destructor
 * */
UComDriverIn::~UComDriverIn()
{
	m_udpSocket.close();
}
