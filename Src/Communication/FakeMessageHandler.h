
/*
#ifndef COMMUNICATION_FAKEMESSAGEHANDLER_H_
#define COMMUNICATION_FAKEMESSAGEHANDLER_H_

class UActuatorHandler;
class USensorHandler;

#include "mbed.h"
#include "defines.h"
#include "USensorType.h"
#include "USensorHandler.h"
#include "UActuatorHandler.h"

class FakeMessageHandler
{
private:

    Serial serial;
    USensorHandler* m_sensorHandler;
    UActuatorHandler* m_actuatorHandler;
    
    char m_RxBuffer[BUFFER_SIZE];
    int m_RxCount;

    void ReadChar();
 
public:
    
    FakeMessageHandler(); // Public Constructor
    
    void initialize(USensorHandler*, UActuatorHandler*);
    void start();
    void resetBuffer();
    void ReadValueFromSensor(int a_sensorId, int a_value);
    void SendMessage(char* message); 
    void CharReceived(char c);
    void OnMessageRecieved(char* message);
    
};

#endif  // COMMUNICATION_FAKEMESSAGEHANDLER_H_
*/
