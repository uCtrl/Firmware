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
#include "cfg.h"
#include "EthernetInterface.h"
#include "UMsgHandlerMailType.h"

extern Mail<UMsgHandlerMailType, COMDRIVER_OUT_MAIL_SIZE> comDriverOutMail;

class UComDriverOut
{
    private:
        UDPSocket m_udpSocket;
        //Endpoint m_udpClient;
        Serial m_uart;
        //DigitalOut m_led;
        uint16_t m_rxCount;
    public:
        UComDriverOut();
        void start();
        void handleMsg();
        ~UComDriverOut();
};

#endif  // UCOMDRIVEROUT_H_

