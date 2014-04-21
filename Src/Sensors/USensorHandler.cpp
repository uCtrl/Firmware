#include "USensorHandler.h"

USensorHandler::USensorHandler(FakeMessageHandler* messageHandler)
{
	m_messageHandler = messageHandler;
	m_SensorCount = 0;
	m_delayBetweenSensorPooling = 1000;
	m_timeElapsed = 0;
	m_timeForNextSleep = 0;
}

void USensorHandler::StartPoolingSensors()
{
	while(1) {

	    for(int i = 0; i < m_SensorCount; i++) {
	    	if((m_timeElapsed % m_Sensors[i]->GetTimeBetweenReads()) == 0) {
	    		m_Sensors[i]->Read();
	    	}
	    }

	    if(m_timeForNextSleep != 0) {
	    	Thread::wait(m_timeForNextSleep);
			m_timeElapsed += m_timeForNextSleep;
			m_timeForNextSleep = 0;
	    } else {
	    	Thread::wait(m_delayBetweenSensorPooling);
			m_timeElapsed += m_delayBetweenSensorPooling;
	    }

	    /*
	    char tmp[10];
	    sprintf(tmp,"%d", m_timeElapsed);
	    m_messageHandler->SendMessage(tmp);

	    char tmp2[10];
	    sprintf(tmp2,"%d", m_delayBetweenSensorPooling);
	    m_messageHandler->SendMessage(tmp2);*/
	}
}

bool USensorHandler::AddNewSensor(USensorType type, char* sensorName, int pinUsed, int timeBetweenReads)
{
    if(m_SensorCount >= SENSOR_LIST_LENGTH)
    {
        return false;
    }

    switch(type)
    {
        case Temperature:
            m_Sensors[m_SensorCount] = new USensorTemperature(m_messageHandler, sensorName, pinUsed, timeBetweenReads);
            break;
        case Light:
            m_Sensors[m_SensorCount] = new USensorLight(m_messageHandler, sensorName, pinUsed, timeBetweenReads);
        case Motion:
            break;
        case Current:
            break;
        default:
            m_Sensors[m_SensorCount] = new USensor(m_messageHandler, sensorName, pinUsed, timeBetweenReads);
            break;
    }
    m_SensorCount++;

    UpdateDelayBetweenReads();
    return true;
}

bool USensorHandler::DeleteSensor(char* sensorName) {

    for(int i = 0; i < m_SensorCount; i++) {

        if(strcmp(sensorName, m_Sensors[i]->GetName()) == 0) {
            delete m_Sensors[i];

            char buf[BUFFER_SIZE] = {0};
            strcat(buf,"Deleted sensor: ");
            strcat(buf,sensorName);

            m_messageHandler->SendMessage(buf);

            // We now need to shift the sensors in the array by 1 position
            for(int j = i; j < m_SensorCount; j++) {
                if(j+1 < SENSOR_LIST_LENGTH) {
                    m_Sensors[j] = m_Sensors[j+1];

                // If we are out of the array bounds
                } else {
                    m_Sensors[j] = NULL;
                }
            }

            m_SensorCount--;
            UpdateDelayBetweenReads();

            return true;
        }
    }

    return false;
}


void USensorHandler::UpdateDelayBetweenReads()
{
	int values[SENSOR_LIST_LENGTH] = {0};

    for(int i = 0; i < m_SensorCount; i++)
    {
    	values[i] = m_Sensors[i]->GetTimeBetweenReads();
    	/*
        char tmp[10];
        sprintf(tmp,"%d", m_Sensors[i]->GetTimeBetweenReads());
        m_messageHandler->SendMessage(tmp);*/
    }

    m_delayBetweenSensorPooling = UMathUtils::gcdOfMultipleNumbers(values, m_SensorCount);

    // We dont want to use all the cpu for nothing
    if(m_delayBetweenSensorPooling == 0)
    {
    	m_delayBetweenSensorPooling = 1000;
    }

    /*
    char tmp[10];
    sprintf(tmp,"%d", m_delayBetweenSensorPooling);

    m_messageHandler->SendMessage("Updated delay between reads:");
    m_messageHandler->SendMessage(tmp);*/

    m_timeForNextSleep = m_delayBetweenSensorPooling - (m_timeElapsed % m_delayBetweenSensorPooling);
}

char** USensorHandler::GetSensorNames()
{
    char** tmp = new char*[SENSOR_NAME_LENGTH];

    return tmp;
}
