/*
* UComDriverOut.h
*
* Created on: Mar 23, 2014
* Author: µCtrl
*/

#ifndef UCOMDRIVEROUT_H_
#define UCOMDRIVEROUT_H_

#include "mbed.h"
#include "rtos.h"
#include "UComDriverOutMailType.h"

extern Mail<UComDriverOutMailType, 2> comDriverOutMail;

class UComDriverOut
{
    private:
        Serial m_uart;
        DigitalOut led;
    public:
        UComDriverOut();
        void start();
        void handleMsg();
        ~UComDriverOut();
};

#endif  // UCOMDRIVEROUT_H_
