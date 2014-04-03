#ifndef COMMUNICATION_FAKEMESSAGEHANDLER_H_
#define COMMUNICATION_FAKEMESSAGEHANDLER_H_

#include "mbed.h"
#include "defines.h"
#include "USensorType.h"
#include "USensorHandler.h"
#include "UActuatorHandler.h"

class FakeMessageHandler
{
private:
    static bool instanceFlag;
    static FakeMessageHandler *instance;
    Serial serial;
    
    char m_RxBuffer[BUFFER_SIZE];
    int m_RxCount;
    
    FakeMessageHandler(); // Private Constructor
 
public:
    
    static FakeMessageHandler* GetInstance();
    
    void start();
    void resetBuffer();
    void ReadValueFromSensor(char* sensorName, int value);
    void SendMessage(char* message); 
    void CharReceived(char c);
    void OnMessageRecieved(char* message);
    
};

#endif  // COMMUNICATION_FAKEMESSAGEHANDLER_H_
