#ifndef UCOMDRIVER_H_
#define UCOMDRIVER_H_

#include "mbed.h"

#define UCOM_BUFFER_SIZE 255

class UComDriver
{
    private:
        Serial m_uart;
        char m_rxBuffer[UCOM_BUFFER_SIZE];
        uint16_t m_rxCount;
    public:
        UComDriver();
        void resetBuffer();
        void start();
        void handleMsg();
        ~UComDriver();
};

#endif  // UCOMDRIVER_H_
