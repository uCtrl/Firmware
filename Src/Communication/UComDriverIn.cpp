/*
* UComDriverIn.cpp
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#include "UComDriverIn.h"

extern Serial usbSerial;

/*
 * Constructor
 * */
UComDriverIn::UComDriverIn() : m_uart(USBTX, USBRX), m_led(LED2)
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
		usbSerial.printf("\n\r - LWIP Mode - \n\r");

	    EthernetInterface eth;
	    if(USE_DHCP) 
	    {
			usbSerial.printf("\n\r - DHCP - \n\r");
	    	eth.init(); //Use DHCP
	    	usbSerial.printf("MAC address : %s\n\r", eth.getMACAddress());
    	}
	    else 
	    {
	    	eth.init("192.168.0.120", "255.255.255.0", "192.168.0.1"); //Use DHCP
	    }
	    eth.connect();
	    
	    UJsonUtils::SetIpAddress(eth.getIPAddress());
	    usbSerial.printf("IP Address is %s\n\r", UJsonUtils::GetIpAddress());

		NTPClient ntp;

		if (ntp.setTime("0.ca.pool.ntp.org") == 0)
		{
		  time_t ctTime;
		  ctTime = time(NULL);
		  printf("Time is set to (UTC): %s\r\n", ctime(&ctTime));
		}
		else
		{
		  printf("Time Set Error\r\n");
		} 

	    m_udpSocket.bind(UDPSOCKET_PORT);	    
	    usbSerial.printf("UDP Socket binded to port %d\n\r", UDPSOCKET_PORT);
	    
	    // Enable broadcast or multicast
	    if(USE_BROADCAST)
	    {
	    	m_udpSocket.set_broadcasting();
		}
    	if(USE_MULTICAST)
		{
		    const char* group = "224.1.1.1";
		    if (m_udpSocket.join_multicast_group(group) != 0) 
		    {
		        printf("Error joining the multicast group %s\r\n", group);
		        while (true) {}
		    }
		    else
		    {
		        printf("Joined multicast group %s\r\n", group);
	    	}
	    }

	    while(true)
		{
#ifdef DEBUG_PRINT
	    	usbSerial.printf("Waiting for packet...\n\r");
#endif
	        m_rxCount = m_udpSocket.receiveFrom(m_udpClient, m_rxBuffer, sizeof(m_rxBuffer));    	 	
	        m_rxBuffer[m_rxCount++] = '\0';
	        handleMsg();
	        //m_led = !m_led;	//led flashing on input
	    	Thread::wait(10);
		}
	}
	else
	{
		usbSerial.printf("\n\r - Serial Mode - \n\r");
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
		mail->endPoint = new Endpoint(m_udpClient);
		
		//char* host = new char[17];
		//strcpy(host, m_udpClient.get_address());		
	    //mail->endPoint->set_address(host,  m_udpClient.get_port());
	}
	
	strncpy(mail->msg, m_rxBuffer, m_rxCount);

#ifdef DEBUG_PRINT
	usbSerial.printf("Message recieved from %s\n\r", m_udpClient.get_address());
#endif

	msgHandlerMail.put(mail);
}

/*
 * Destructor
 * */
UComDriverIn::~UComDriverIn()
{
	m_udpSocket.close();
}

