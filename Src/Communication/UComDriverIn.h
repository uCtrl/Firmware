/*
* UComDriverIn.h
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#ifndef UCOMDRIVERIN_H_
#define UCOMDRIVERIN_H_

#include "mbed.h"
#include "rtos.h"
#include "UMsgHandlerMailType.h"

#define UCOMIN_BUFFER_SIZE 255

extern Mail<UMsgHandlerMailType, 2> msgHandlerMail;

class UComDriverIn
{
    private:
        Serial m_uart;
        DigitalOut led;
        char m_rxBuffer[UCOMIN_BUFFER_SIZE];
        uint16_t m_rxCount;
    public:
        UComDriverIn();
        void resetBuffer();
        void start();
        void handleMsg();
        ~UComDriverIn();
};

#endif  // UCOMDRIVERIN_H_
