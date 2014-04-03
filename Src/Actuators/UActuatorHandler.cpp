#include "UActuatorHandler.h"

bool UActuatorHandler::instanceFlag = false;
UActuatorHandler* UActuatorHandler::instance = NULL;

// Private Constructor
UActuatorHandler::UActuatorHandler()
{
	m_ActuatorCount = 0;
}


// Get the singleton instance
UActuatorHandler* UActuatorHandler::GetInstance()
{
    if(! instanceFlag)
    {
        instance = new UActuatorHandler();
        instanceFlag = true;
        return instance;
    }
    else
    {
        return instance;
    }
}

bool UActuatorHandler::AddNewActuator(UActuatorType a_type, char* a_actuatorName, int a_pinUsed)
{
    if(m_ActuatorCount >= ACTUATORS_LIST_LENGTH)
    {
        return false;
    }

    switch(a_type)
    {
        case Actuator_Fake:
            m_Actuators[m_ActuatorCount] = new FakeActuator(a_actuatorName, a_pinUsed);
            break;
    }

    m_ActuatorCount++;
    return true;
}

bool UActuatorHandler::DeleteActuator(char* a_actuatorName)
{
    for(int i = 0; i < m_ActuatorCount; i++) {

        if(strcmp(a_actuatorName, m_Actuators[i]->GetName()) == 0) {
            delete m_Actuators[i];

            char buf[BUFFER_SIZE] = {0};
            strcat(buf, "Deleted actuator: ");
            strcat(buf, a_actuatorName);

            FakeMessageHandler::GetInstance()->SendMessage(buf);

            // We now need to shift the sensors in the array by 1 position
            for(int j = i; j < m_ActuatorCount; j++) {
                if(j+1 < ACTUATORS_LIST_LENGTH) {
                    m_Actuators[j] = m_Actuators[j+1];

                // If we are out of the array bounds
                } else {
                    m_Actuators[j] = NULL;
                }
            }

            m_ActuatorCount--;
            return true;
        }
    }
    return false;
}

bool UActuatorHandler::SetActuatorValue(char* a_actuatorName, int a_value)
{
    for(int i = 0; i < m_ActuatorCount; i++) {
        if(strcmp(a_actuatorName, m_Actuators[i]->GetName()) == 0) {
            m_Actuators[i]->SetValue(a_value);
            return true;
        }
    }
    return false;
}

char** UActuatorHandler::GetActuatorNames()
{
    char** tmp = new char*[ACTUATORS_NAME_LENGTH];

    return tmp;
}
