#include "FakeMessageHandler.h"

bool FakeMessageHandler::instanceFlag = false;
FakeMessageHandler* FakeMessageHandler::instance = NULL;

void FakeMessageHandler::OnMessageRecieved(char* message)
{
    // Sensors
    if(strcmp(message, "CreateSensor1") == 0)
    {
        serial.printf("Creating MyNewFakeSensor1\n\r");
        USensorHandler::GetInstance()->AddNewSensor(Fake, "MyNewFakeSensor1", 0);
    }
    if(strcmp(message, "CreateSensor2") == 0)
    {
        serial.printf("Creating MyNewFakeSensor2\n\r");
        USensorHandler::GetInstance()->AddNewSensor(Fake, "MyNewFakeSensor2", 1);
    }
    if(strcmp(message, "DeleteSensor1") == 0)
    {
        serial.printf("Trying to delete MyNewFakeSensor1\n\r");
        USensorHandler::GetInstance()->DeleteSensor("MyNewFakeSensor1");
    }
    if(strcmp(message, "DeleteSensor2") == 0)
    {
        serial.printf("Trying to delete MyNewFakeSensor2\n\r");
        USensorHandler::GetInstance()->DeleteSensor("MyNewFakeSensor2");
    }
    
    // Actuators
    if(strcmp(message, "CreateActuator1") == 0)
    {
        serial.printf("Creating MyNewFakeActuator1\n\r");
        UActuatorHandler::GetInstance()->AddNewActuator(Actuator_Fake, "MyNewFakeActuator1", 0);
    }
    if(strcmp(message, "CreateActuator2") == 0)
    {
        serial.printf("Creating MyNewFakeActuator2\n\r");
        UActuatorHandler::GetInstance()->AddNewActuator(Actuator_Fake, "MyNewFakeActuator2", 1);
    }
    if(strcmp(message, "DeleteActuator1") == 0)
    {
        serial.printf("Trying to delete MyNewFakeSensor1\n\r");
        UActuatorHandler::GetInstance()->DeleteActuator("MyNewFakeActuator1");
    }
    if(strcmp(message, "DeleteActuator2") == 0)
    {
        serial.printf("Trying to delete MyNewFakeActuator2\n\r");
        UActuatorHandler::GetInstance()->DeleteActuator("MyNewFakeActuator2");
    }
}

// Private Constructor
FakeMessageHandler::FakeMessageHandler() : serial(USBTX, USBRX)
{    
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        m_RxBuffer[i] = 0;        
    }
    
    m_RxCount = 0;
}

void FakeMessageHandler::start()
{
    serial.printf("FakeMessageHandler ready.\r\n");
    while(1)
    {
	    char c = serial.getc();
	    CharReceived(c);
	}
}

// Get the singleton instance
FakeMessageHandler* FakeMessageHandler::GetInstance()
{
    if(!instanceFlag)
    {
        instance = new FakeMessageHandler();
        instanceFlag = true;
        return instance;
    }
    else
    {
        return instanceFlag;
    }
}

void FakeMessageHandler::resetBuffer()
{
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        m_RxBuffer[i] = 0;
    }

    m_RxCount = 0;
}

void FakeMessageHandler::SendMessage(char* message)
{
    serial.printf(message);
    serial.printf("\r\n");
}

void FakeMessageHandler::ReadValueFromSensor(char* sensorName, int value)
{
    // Convert int to str
	/*
    char tmp[10];
    sprintf(tmp,"%d",value);
    
    char buf[BUFFER_SIZE] = {0};
    strcat(buf,"Captured input from sensor ");
    strcat(buf,sensorName);
    strcat(buf,", value : ");
    strcat(buf,tmp);
    SendMessage(buf);//*/
    
    if(strcmp(sensorName, "MyNewFakeSensor1") == 0)
    {
        if(value > 55000) {
            UActuatorHandler::GetInstance()->SetActuatorValue("MyNewFakeActuator1", 1);
        } else {
            UActuatorHandler::GetInstance()->SetActuatorValue("MyNewFakeActuator1", 0);
        }
    }
    
    if(strcmp(sensorName, "MyNewFakeSensor2") == 0)
    {
        if(value > 55000) {
            UActuatorHandler::GetInstance()->SetActuatorValue("MyNewFakeActuator2", 1);
        } else {
            UActuatorHandler::GetInstance()->SetActuatorValue("MyNewFakeActuator2", 0);
        }
    }
}

// Stores the characters received in a rx buffer. If a enter is received, sends the message
// Really basic stuff for testing
void FakeMessageHandler::CharReceived(char c)
{
    if(c == 13) // enter
    {
        serial.printf("\n\r");
        serial.printf("Message Sent: ");
        serial.printf(m_RxBuffer);
        serial.printf("\n\r");
        
        OnMessageRecieved(m_RxBuffer);
        resetBuffer();
    }    
    else
    {    
        serial.putc(c);
        m_RxBuffer[m_RxCount] = c;

        m_RxCount++;            
        if(m_RxCount == BUFFER_SIZE)
            m_RxCount = 0;         
    }
}
