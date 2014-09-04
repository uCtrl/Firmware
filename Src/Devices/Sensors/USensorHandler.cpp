#include "USensorHandler.h"

USensorHandler::USensorHandler()
{
	m_SensorCount = 0;
	m_delayBetweenSensorPooling = 1000;
	m_timeElapsed = 0;
	m_timeForNextSleep = 0;
}

void USensorHandler::StartPoolingSensors()
{
	while(1) {

		// Wait
	    if(m_timeForNextSleep != 0) {
	    	Thread::wait(m_timeForNextSleep);
			m_timeElapsed += m_timeForNextSleep;
			m_timeForNextSleep = 0;
	    } else {
	    	Thread::wait(m_delayBetweenSensorPooling);
			m_timeElapsed += m_delayBetweenSensorPooling;
	    }

	    // Execute read on all sensors
	    for(int i = 0; i < m_SensorCount; i++) {
	    	if((m_timeElapsed % m_Sensors[i]->GetTimeBetweenReads()) == 0) {
	    		m_Sensors[i]->Read();
	    	}
	    }
	}
}

bool USensorHandler::AddNewSensor(USensorType type, int a_sensorId, int a_pinUsed, int a_timeBetweenReads, char* a_sensorName)
{
    if(m_SensorCount >= SENSOR_LIST_LENGTH)
    {
        return false;
    }

	printf("Created sensor!\r\n");

    switch(type)
    {
        case Temperature:
            m_Sensors[m_SensorCount] = new USensorTemperature(a_sensorId, a_pinUsed, a_timeBetweenReads, a_sensorName);
            break;
        case Light:
            m_Sensors[m_SensorCount] = new USensorLight(a_sensorId, a_pinUsed, a_timeBetweenReads, a_sensorName);
            break;
        case Motion:
            break;
        case Current:
            break;
        default:
            m_Sensors[m_SensorCount] = new USensor(a_sensorId, a_pinUsed, a_timeBetweenReads, a_sensorName);
            break;
    }
    m_SensorCount++;

    UpdateDelayBetweenReads();
    return true;
}

bool USensorHandler::DeleteSensor(int sensorId) {

    for(int i = 0; i < m_SensorCount; i++) {

        if(sensorId == m_Sensors[i]->GetId()) {
            delete m_Sensors[i];
            /*
            char tmp_id[10];
            sprintf(tmp_id,"%d", sensorId);

            char buf[BUFFER_SIZE] = {0};
            strcat(buf, "Deleted sensor: ");
            strcat(buf, tmp_id);

            m_messageHandler->SendMessage(buf);
			*/

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
    }

    m_delayBetweenSensorPooling = UMathUtils::gcdOfMultipleNumbers(values, m_SensorCount);

    // We dont want to use all the cpu for nothing
    if(m_delayBetweenSensorPooling == 0)
    {
    	m_delayBetweenSensorPooling = 1000;
    }

    m_timeForNextSleep = m_delayBetweenSensorPooling - (m_timeElapsed % m_delayBetweenSensorPooling);
}

char** USensorHandler::GetSensorNames()
{
    char** tmp = new char*[SENSOR_NAME_LENGTH];

    return tmp;
}
