#include "UComDriver.h"

// Private Constructor
UComDriver::UComDriver() : m_uart(USBTX, USBRX), led(LED_GREEN)
{
	m_rxCount = 0;
}

// Private Constructor
UComDriver::~UComDriver()
{
}

void UComDriver::resetBuffer()
{
    //if(DEBUG) m_uart.printf("ResetBuffer");
    for(int i = 0; i < UCOM_BUFFER_SIZE; i++)
    {
        m_rxBuffer[i] = 0;        
    }
    m_rxCount = 0;
}

void UComDriver::start()
{
	led = true;
	char c;
	while(true)
	{
		c = m_uart.getc();
		led = !led;
		if(c == 13) // enterKey
		{
			handleMsg();
			resetBuffer();
		}
		else
		{
			m_rxBuffer[m_rxCount] = c;
			m_rxCount++;

			if(m_rxCount == UCOM_BUFFER_SIZE)
			{
				handleMsg();
				resetBuffer();
			}
		}
		m_uart.putc(c);
	}
}

void UComDriver::handleMsg()
{
	#ifdef DEBUG_PRINT
		m_uart.printf("%s","handle message");
	#endif
    m_uart.printf("\r\nMessage Received : %s\r\n",m_rxBuffer);
}
