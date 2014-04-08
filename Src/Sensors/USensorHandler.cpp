#include "USensorHandler.h"m_SensorCount

USensorHandler::USensorHandler(FakeMessageHandler* messageHandler)
{
	m_messageHandler = messageHandler;
	m_SensorCount = 0;
}

bool USensorHandler::AddNewSensor(USensorType type, char* sensorName, int pinUsed)
{
    if(m_SensorCount >= SENSOR_LIST_LENGTH)
    {
        return false;
    }

    switch(type)
    {
        case Temperature:
            break;
        case Motion:
            break;
        case Current:
            break;
        case Fake:
            m_Sensors[m_SensorCount] = new FakeSensor(m_messageHandler, sensorName, pinUsed, 5000);
            break;
    }

    m_SensorCount++;
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
            return true;
        }
    }
    return false;
}

char** USensorHandler::GetSensorNames()
{
    char** tmp = new char*[SENSOR_NAME_LENGTH];

    return tmp;
}
