/*#ifndef COMMUNICATION_FAKEMESSAGEHANDLER_H_
#define COMMUNICATION_FAKEMESSAGEHANDLER_H_

#include "mbed.h"
#include "MODSERIAL.h"
#include "defines.h"
#include "USensorType.h"
#include "USensorHandler.h"
#include "UActuatorHandler.h"

class FakeMessageHandler
{
private:
    static bool instanceFlag;
    static FakeMessageHandler *instance;
    MODSERIAL serial; 
    
    char m_RxBuffer[BUFFER_SIZE];
    int m_RxCount;
    
    FakeMessageHandler(); // Private Constructor
 
public:
    
    static FakeMessageHandler* GetInstance();
    
    void ReadValueFromSensor(char* sensorName, int value);
    void SendMessage(char* message); 
    void RxInterrupt(MODSERIAL_IRQ_INFO *q);
    void OnMessageRecieved(char* message);
    
};

#endif  // COMMUNICATION_FAKEMESSAGEHANDLER_H_*/
