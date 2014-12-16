/*
* UComDriverOut.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "UComDriverOut.h"

extern Serial usbSerial;

Mail<UMsgHandlerMailType, COMDRIVER_OUT_MAIL_SIZE> comDriverOutMail;

/*
 * Constructor
 * */
UComDriverOut::UComDriverOut() : m_uart(USBTX, USBRX)//, m_led(LED2)
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
			//m_led = !m_led;
			UMsgHandlerMailType *mail = (UMsgHandlerMailType*)evt.value.p;
			if(USE_LWIP)
			{
			    if(mail->endPoint != NULL) 
			    {
#ifdef DEBUG_PRINT
				    //usbSerial.printf("UDP Socket is sending response to %s on port %d\n\r", mail->endPoint->get_address(), mail->endPoint->get_port());
#endif
				    m_udpSocket.init();
				    m_rxCount = m_udpSocket.sendTo(*mail->endPoint, mail->msg, strlen(mail->msg));
        			m_udpSocket.close();
					delete mail->endPoint;
#ifdef DEBUG_PRINT
				    //usbSerial.printf("Send succeed. %d bytes sended\n\r", m_rxCount);
#endif
			    }
			    //else 
			    {
			    	if(SEND_BROADCAST)
			    	{
					    m_udpSocket.init();
					    m_udpSocket.set_broadcasting();
				    	
					    Endpoint broadcast;
					    const int port = BROADCAST_PORT;
						broadcast.set_address("255.255.255.255", port);
					    
					    m_rxCount = m_udpSocket.sendTo(broadcast, mail->msg, strlen(mail->msg));
        				m_udpSocket.close();
#ifdef DEBUG_PRINT
					    usbSerial.printf("UDP Socket is broadcasting on port %d\n\r", broadcast.get_port());
					    usbSerial.printf("Send succeed. %d bytes sended\n\r", m_rxCount);
#endif
				    }
			    	if(SEND_MULTICAST)
				    {
					    m_udpSocket.init();
					    
					    Endpoint multicast_group;
					    const char* group = "224.1.1.1"; //MULTICAST_GRP;
					    const int port = UDPSOCKET_PORT;
					    
					    multicast_group.set_address(group, port);
					    
				    	m_rxCount = m_udpSocket.sendTo(multicast_group, mail->msg, strlen(mail->msg));
        				m_udpSocket.close();
#ifdef DEBUG_PRINT
					    usbSerial.printf("UDP Socket is multicasting to group %s on port %d\n\r", group, multicast_group.get_port());
					    usbSerial.printf("Send succeed. %d bytes sended\n\r", m_rxCount);
#endif
			    	}
			    }
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

