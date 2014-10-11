/*
* UComDriverOut.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "UComDriverOut.h"

Mail<UMsgHandlerMailType, 2> comDriverOutMail;

/*
 * Constructor
 * */
UComDriverOut::UComDriverOut() : m_uart(USBTX, USBRX), m_led(LED2)
{
	m_uart.baud(SERIAL_BAUD);
	m_rxCount = 0;
}

/*
 * Starting thread
 * @return void
 * */
void UComDriverOut::start()
{
	while(true)
	{
		osEvent evt = comDriverOutMail.get();
		if (evt.status == osEventMail)
		{
			m_led = !m_led;
			UMsgHandlerMailType *mail = (UMsgHandlerMailType*)evt.value.p;
			if(USE_LWIP)
			{
			    m_udpSocket.init();
			    //m_udpClient.set_address("192.168.15.102",8);	//TODO msghandler mail doit avoir le endpoint.
			    //printf("UDP Socket is sending response to %s on port %d\n\r", m_udpClient.get_address(), m_udpClient.get_port());
		        printf("UDP Socket is sending response to %s on port %d\n\r", mail->endPoint.get_address(), mail->endPoint.get_port());
		        m_rxCount = m_udpSocket.sendTo(mail->endPoint, mail->msg, strlen(mail->msg));
		        printf("Send succeed. %d bytes sended\n\r", m_rxCount);
			}
			else
			{
				m_uart.puts(mail->msg);
			}
			comDriverOutMail.free(mail);
		}
	}
}

/*
 * Destructor
 * */
UComDriverOut::~UComDriverOut()
{
	m_udpSocket.close();
}
