/*
 * UDeviceHandler.cpp
 *
 *  Created on: Sep 2, 2014
 *      Author: uctrl
 */

#include <UDeviceHandler.h>

extern Serial usbSerial;

UDeviceHandler::UDeviceHandler()
{
	m_SensorCount = 0;
	m_delayBetweenSensorPooling = 1000;
	m_timeElapsed = 0;
	m_timeForNextSleep = 0;

	m_ActuatorCount = 0;
	
	m_Sensors = new USensor*[SENSOR_LIST_LENGTH];
	m_Actuators = new UActuator*[ACTUATORS_LIST_LENGTH];
	
    for(int i = 0; i < SENSOR_LIST_LENGTH; i++) 
    {
		m_Actuators[i] = NULL;
    }

    for(int i = 0; i < SENSOR_LIST_LENGTH; i++) 
    {
		m_Sensors[i] = NULL;
    }

}

UDeviceHandler::~UDeviceHandler()
{
	//Destructor
}

void UDeviceHandler::StartPoolingSensors()
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

bool UDeviceHandler::AddNewSensor(UDevice* a_device, int a_pinUsed, int a_timeBetweenReads)
{
    if(m_SensorCount >= SENSOR_LIST_LENGTH)
    {
        return false;
    }

    switch(a_device->DeviceType)
    {
		case Sensor_Light:
			m_Sensors[m_SensorCount] = new USensorLight(a_device, a_pinUsed, a_timeBetweenReads);
			break;
        case Sensor_Temperature:
            m_Sensors[m_SensorCount] = new USensorTemperature(a_device, a_pinUsed, a_timeBetweenReads);
            break;
        case Sensor_Motion:
            break;
        default:
            m_Sensors[m_SensorCount] = new USensor(a_device, a_pinUsed, a_timeBetweenReads);
            break;
    }
    m_SensorCount++;

    UpdateDelayBetweenReads();
    return true;
}

bool UDeviceHandler::DeleteSensor(int sensorId)
{
    int count = m_SensorCount;
    for(int i = 0; i < count; i++) 
    {
        if(sensorId == m_Sensors[i]->Device->DeviceID) 
        {
            delete m_Sensors[i];

            // We now need to shift the sensors in the array by 1 position
            for(int j = i; j < count-1; j++) {
                m_Sensors[j] = m_Sensors[j+1];
            }
            m_Sensors[count-1] = NULL;

            m_SensorCount--;
            UpdateDelayBetweenReads();
            return true;
        }
    }

    return false;
}


bool UDeviceHandler::AddNewActuator(UDevice* device, int a_pinUsed)
{
    if(m_ActuatorCount >= ACTUATORS_LIST_LENGTH)
    {
        return false;
    }
        	
    switch(device->DeviceType)
    {
        case Actuator_Switch:
            m_Actuators[m_ActuatorCount] = new USwitchActuator(device, a_pinUsed);
            break;
        case Actuator_RGB:
            m_Actuators[m_ActuatorCount] = new USwitchActuator(device, a_pinUsed);
            break;
        case Actuator_LedsFlow:
            m_Actuators[m_ActuatorCount] = new USwitchActuator(device, a_pinUsed);
            break;
    }

    m_ActuatorCount++;
    return true;
}

bool UDeviceHandler::DeleteActuator(int a_actuatorId)
{		    
    int count = m_ActuatorCount;
    for(int i = 0; i < count; i++) 
    {
        if(a_actuatorId == m_Actuators[i]->Device->DeviceID) 
        {
            delete m_Actuators[i];

            // We now need to shift the actuators in the array by 1 position
            for(int j = i; j < count-1; j++) {
                m_Actuators[j] = m_Actuators[j+1];
            }
            m_Actuators[count-1] = NULL;

            m_ActuatorCount--;
            return true;
        }
    }
    return false;
}

bool UDeviceHandler::AddDevice(UDevice *mDevice)
{		
	int pin = 0;
	int timeBetweenReads;

	// Actuators
	if(mDevice->DeviceID == 3)
		pin = 0;
	if(mDevice->DeviceID == 20)
		pin = 1;
	if(mDevice->DeviceID == 30)
		pin = 2;
	if(mDevice->DeviceID == 40)
		pin = 3;
	if(mDevice->DeviceID == 50)
		pin = 4;
	if(mDevice->DeviceID == 60)
		pin = 5;
	if(mDevice->DeviceID == 70)
		pin = 6;
		
	// Sensors
	if(mDevice->DeviceID == 2) 
		pin = 0;
	if(mDevice->DeviceID == 80)
		pin = 1;
	if(mDevice->DeviceID == 100 || mDevice->DeviceID == 110)
		pin = 2;
		
				
	switch(mDevice->DeviceType) {
		case Actuator_Switch:	
			return AddNewActuator(mDevice, pin);
			
		case Actuator_RGB:	
			return AddNewActuator(mDevice, pin);
			
		case Actuator_LedsFlow:	
			return AddNewActuator(mDevice, pin);

		case Sensor_Light:
			timeBetweenReads = 2000;
			return AddNewSensor(mDevice, pin, timeBetweenReads);

		case Sensor_Temperature:
			timeBetweenReads = 2000;
			return AddNewSensor(mDevice, pin, timeBetweenReads);

		case Sensor_Motion:
			timeBetweenReads = 5000;
			return AddNewSensor(mDevice, pin, timeBetweenReads);

		default:
			break;
	}
	return 0;
}

bool UDeviceHandler::DeleteDevice(UDevice* device)
{
	return DeleteDevice(device->DeviceID);
}

bool UDeviceHandler::DeleteDevice(int deviceId)
{
	if(DeleteActuator(deviceId))
		return true;
	if(DeleteSensor(deviceId))
		return true;
	
	return false;
}

bool UDeviceHandler::SetActuatorValue(int a_actuatorId, string a_value)
{
//#ifdef DEBUG_PRINT
	//usbSerial.printf("Set Actuator %d to value %s\r\n", GetDevice(a_actuatorId)->DeviceID, a_value.c_str());
//#endif

    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	if(m_Actuators[i] != NULL && m_Actuators[i]->Device != NULL && m_Actuators[i]->Device->DeviceID == a_actuatorId) {
            m_Actuators[i]->SetValue(a_value);
            return true;
    	} else {
    		//usbSerial.printf("Actuator count is %d, but actuator at %d is NULL\r\n", m_ActuatorCount, i);
    	}
    }

    return false;
}

void UDeviceHandler::UpdateDelayBetweenReads()
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

void UDeviceHandler::GetDeviceIds(int* Ids)
{
	int count = 0;

    for(int i = 0; i < m_SensorCount; i++)
    {
		Ids[count] = m_Sensors[i]->Device->DeviceID;
    	count++;
    }

    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	Ids[count] = m_Actuators[i]->Device->DeviceID;
    	count++;
    }
}

USensor* UDeviceHandler::GetSensor(int a_deviceId)
{
    for(int i = 0; i < m_SensorCount; i++)
    {
    	if(m_Sensors[i]->Device->DeviceID == a_deviceId) {
    		return m_Sensors[i];
    	}
    }
    return NULL;
}

UDevice* UDeviceHandler::GetDevice(int a_deviceId)
{
    for(int i = 0; i < m_SensorCount; i++)
    {
    	if(m_Sensors[i]->Device->DeviceID == a_deviceId) {
    		return m_Sensors[i]->Device;
    	}
    }

    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	if(m_Actuators[i]->Device->DeviceID == a_deviceId) {
    		return m_Actuators[i]->Device;
    	}
    }

    return NULL;
}

UActuator* UDeviceHandler::GetActuator(int a_deviceId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	if(m_Actuators[i]->Device->DeviceID == a_deviceId) {
    		return m_Actuators[i];
    	}
    }
    return NULL;
}

UScenario* UDeviceHandler::GetScenario(int a_scenarioId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
        for(int j = 0; j < device->ScenarioCount; j++)
        {
        	if(device->ScenarioList[j]->ScenarioID == a_scenarioId) {
        		return device->ScenarioList[j];
        	}
        }
    }

    return NULL;
}

UTask* UDeviceHandler::GetTask(int a_taskId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
        for(int j = 0; j < device->ScenarioCount; j++)
        {
			UScenario* scenario = device->ScenarioList[j];
			for(int k = 0; k < scenario->TaskCount; k++)
			{
				if(scenario->TaskList[k]->TaskID == a_taskId) {
					return scenario->TaskList[k];
				}
			}
		}
    }

    return NULL;
}

UCondition* UDeviceHandler::GetCondition(int a_ConditionId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
        for(int j = 0; j < device->ScenarioCount; j++)
        {
			UScenario* scenario = device->ScenarioList[j];
			for(int k = 0; k < scenario->TaskCount; k++)
			{
				UTask* task = scenario->TaskList[k];
				for(int l = 0; l < task->ConditionListIndex; l++)
				{
					if(task->ConditionList[l]->ConditionId == a_ConditionId) {
						return task->ConditionList[l];
					}
				}
			}
		}
    }

    return NULL;
}

bool UDeviceHandler::DeleteScenario(int a_scenarioId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
        for(int j = 0; j < device->ScenarioCount; j++)
        {
        	if(device->ScenarioList[j]->ScenarioID == a_scenarioId) {
        		device->DelScenario(a_scenarioId);
        		return true;
        	}
        }
    }

    return false;
}

bool UDeviceHandler::DeleteTask(int a_taskId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
        for(int j = 0; j < device->ScenarioCount; j++)
        {
			UScenario* scenario = device->ScenarioList[j];
			for(int k = 0; k < scenario->TaskCount; k++)
			{
				if(scenario->TaskList[k]->TaskID == a_taskId) {
	        		scenario->DelTask(a_taskId);
	        		return true;
				}
			}
		}
    }

    return false;
}

bool UDeviceHandler::DeleteCondition(int a_ConditionId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
        for(int j = 0; j < device->ScenarioCount; j++)
        {
			UScenario* scenario = device->ScenarioList[j];
			for(int k = 0; k < scenario->TaskCount; k++)
			{
				UTask* task = scenario->TaskList[k];
				for(int l = 0; l < task->ConditionListIndex; l++)
				{
					usbSerial.printf("for task l = %d\n\r", l);
					
					if(task->ConditionList[l]->ConditionId == a_ConditionId) {
		        		task->DelCondition(a_ConditionId);
		        		return true;
					}
				}
			}
		}
    }

    return false;
}

int UDeviceHandler::UpdateConditions(int a_SensorId, int a_Value)
{
    int updatedConditions = 0;
    
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
        for(int j = 0; j < device->ScenarioCount; j++)
        {
			UScenario* scenario = device->ScenarioList[j];
			for(int k = 0; k < scenario->TaskCount; k++)
			{
				UTask* task = scenario->TaskList[k];
				for(int l = 0; l < task->ConditionListIndex; l++)
				{
					if(task->ConditionList[l]->DeviceId == a_SensorId) {
						task->ConditionList[l]->UpdateSensorValue(a_Value);
						updatedConditions++;
					}
				}
			}
		}
    }

    return updatedConditions;
}

void UDeviceHandler::DeleteDevices()
{
	int actuatorCount = m_ActuatorCount;
    for(int i = 0; i < actuatorCount; i++)
    {	
    	UDevice* device = m_Actuators[0]->Device;
    	DeleteDevice(device);
    }

	int sensorCount = m_SensorCount;
    for(int i = 0; i < sensorCount; i++)
    {
    	UDevice* device = m_Sensors[0]->Device;
    	DeleteDevice(device);
    }
}

void UDeviceHandler::DeleteScenarios(int a_deviceId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
    	if(device->DeviceID == a_deviceId)
    	{
	        for(int j = 0; j < device->ScenarioCount; j++)
	        {
				usbSerial.printf("Deleting scenario %d\r\n", device->ScenarioList[0]->ScenarioID);
        		device->DelScenario(device->ScenarioList[0]->ScenarioID);
        	}
        }
    }
}

void UDeviceHandler::DeleteTasks(int a_scenarioId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
        for(int j = 0; j < device->ScenarioCount; j++)
        {
			UScenario* scenario = device->ScenarioList[j];
			if(scenario->ScenarioID == a_scenarioId)
			{
				for(int k = 0; k < scenario->TaskCount; k++)
				{
	        		scenario->DelTask(scenario->TaskList[0]->TaskID);
				}
			}
		}
    }
}

void UDeviceHandler::DeleteConditions(int a_taskId)
{
    for(int i = 0; i < m_ActuatorCount; i++)
    {
    	UDevice* device = m_Actuators[i]->Device;
        for(int j = 0; j < device->ScenarioCount; j++)
        {
			UScenario* scenario = device->ScenarioList[j];
			for(int k = 0; k < scenario->TaskCount; k++)
			{
				UTask* task = scenario->TaskList[k];
				if(task->TaskID == a_taskId)
				{
					for(int l = 0; l < task->ConditionListIndex; l++)
					{
		        		task->DelCondition(task->ConditionList[0]->ConditionId);
					}
				}
			}
		}
    }
}