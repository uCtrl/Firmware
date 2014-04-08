#include "FakeMessageHandler.h"

FakeMessageHandler::FakeMessageHandler() : serial(USBTX, USBRX)
{
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        m_RxBuffer[i] = 0;
    }
    
    m_RxCount = 0;
    m_actuatorHandler = NULL;
    m_sensorHandler = NULL;
}

void FakeMessageHandler::initialize(USensorHandler* sensorHandler, UActuatorHandler* actuatorHandler) {
    m_sensorHandler = sensorHandler;
    m_actuatorHandler = actuatorHandler;
}

void FakeMessageHandler::start()
{
    serial.printf("FakeMessageHandler ready.\r\n");

    //serial.attach(this, &FakeMessageHandler::ReadChar, Serial::RxIrq);

    while(1)
    {
	    ReadChar();
	}
}

void FakeMessageHandler::ReadChar()
{
    char c = serial.getc();
    CharReceived(c);
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
        	m_actuatorHandler->SetActuatorValue("MyNewFakeActuator1", 1);
        } else {
        	m_actuatorHandler->SetActuatorValue("MyNewFakeActuator1", 0);
        }
    }
    
    if(strcmp(sensorName, "MyNewFakeSensor2") == 0)
    {
        if(value > 55000) {
        	m_actuatorHandler->SetActuatorValue("MyNewFakeActuator2", 1);
        } else {
        	m_actuatorHandler->SetActuatorValue("MyNewFakeActuator2", 0);
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

void FakeMessageHandler::OnMessageRecieved(char* message)
{
    // Sensors
    if(strcmp(message, "CreateSensor1") == 0)
    {
        serial.printf("Creating MyNewFakeSensor1\n\r");
        m_sensorHandler->AddNewSensor(Fake, "MyNewFakeSensor1", 0);
    }
    if(strcmp(message, "CreateSensor2") == 0)
    {
        serial.printf("Creating MyNewFakeSensor2\n\r");
        m_sensorHandler->AddNewSensor(Fake, "MyNewFakeSensor2", 1);
    }
    if(strcmp(message, "DeleteSensor1") == 0)
    {
        serial.printf("Trying to delete MyNewFakeSensor1\n\r");
        m_sensorHandler->DeleteSensor("MyNewFakeSensor1");
    }
    if(strcmp(message, "DeleteSensor2") == 0)
    {
        serial.printf("Trying to delete MyNewFakeSensor2\n\r");
        m_sensorHandler->DeleteSensor("MyNewFakeSensor2");
    }

    // Actuators
    if(strcmp(message, "CreateActuator1") == 0)
    {
        serial.printf("Creating MyNewFakeActuator1\n\r");
        m_actuatorHandler->AddNewActuator(Actuator_Fake, "MyNewFakeActuator1", 0);
    }
    if(strcmp(message, "CreateActuator2") == 0)
    {
        serial.printf("Creating MyNewFakeActuator2\n\r");
        m_actuatorHandler->AddNewActuator(Actuator_Fake, "MyNewFakeActuator2", 1);
    }
    if(strcmp(message, "DeleteActuator1") == 0)
    {
        serial.printf("Trying to delete MyNewFakeSensor1\n\r");
        m_actuatorHandler->DeleteActuator("MyNewFakeActuator1");
    }
    if(strcmp(message, "DeleteActuator2") == 0)
    {
        serial.printf("Trying to delete MyNewFakeActuator2\n\r");
        m_actuatorHandler->DeleteActuator("MyNewFakeActuator2");
    }
}
