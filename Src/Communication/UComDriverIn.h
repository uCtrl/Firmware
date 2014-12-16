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
#include "NTPClient.h"

#include "cfg.h"
#include "EthernetInterface.h"
#include "UMsgHandlerMailType.h"
#include "UJsonUtils.h"

//#include "redefinitionOfNewAndDelete.h"

extern Mail<UMsgHandlerMailType, MSGHANDLER_MAIL_SIZE> msgHandlerMail;

class UComDriverIn
{
    private:
        UDPSocket m_udpSocket;
        Endpoint m_udpClient;
        Serial m_uart;
        DigitalOut m_led;
        char m_rxBuffer[COM_BUFFER_SIZE];
        uint16_t m_rxCount;
    public:
        UComDriverIn();
        void resetBuffer();
        void start();
        void handleMsg();
        ~UComDriverIn();
};

#endif  // UCOMDRIVERIN_H_

