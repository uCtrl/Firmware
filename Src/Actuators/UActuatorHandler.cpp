#include "UActuatorHandler.h"

UActuatorHandler::UActuatorHandler(FakeMessageHandler* messageHandler)
{
	m_messageHandler = messageHandler;
	m_ActuatorCount = 0;
}

bool UActuatorHandler::AddNewActuator(UActuatorType a_type, int a_actuatorId, int a_pinUsed)
{
    if(m_ActuatorCount >= ACTUATORS_LIST_LENGTH)
    {
        return false;
    }

    switch(a_type)
    {
        case Actuator_Fake:
            m_Actuators[m_ActuatorCount] = new FakeActuator(a_actuatorId, a_pinUsed);
            break;
    }

    m_ActuatorCount++;
    return true;
}

bool UActuatorHandler::DeleteActuator(int a_actuatorId)
{
    for(int i = 0; i < m_ActuatorCount; i++) {

        if(a_actuatorId == m_Actuators[i]->GetId()) {
            delete m_Actuators[i];

            char tmp_id[10];
            sprintf(tmp_id,"%d", a_actuatorId);

            char buf[BUFFER_SIZE] = {0};
            strcat(buf, "Deleted actuator: ");
            strcat(buf, tmp_id);

            m_messageHandler->SendMessage(buf);

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
	/*m_messageHandler->SendMessage("test");

    char tmp[10];
    sprintf(tmp,"%d",m_ActuatorCount);
	m_messageHandler->SendMessage(tmp);

	/*
    for(int i = 0; i < m_ActuatorCount; i++) {
        if(strcmp(a_actuatorName, m_Actuators[i]->GetName()) == 0) {
            //m_Actuators[i]->SetValue(a_value);
            return true;
        }
    }*/
    return false;
}

char** UActuatorHandler::GetActuatorNames()
{
    char** tmp = new char*[ACTUATORS_NAME_LENGTH];

    return tmp;
}
