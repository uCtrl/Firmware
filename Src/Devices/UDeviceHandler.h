/*
 * UDeviceHandler.h
 *
 *  Created on: Sep 2, 2014
 *      Author: uctrl
 */

#ifndef UDEVICEHANDLER_H_
#define UDEVICEHANDLER_H_

#include "string.h"
#include "cfg.h"
#include "UMathUtils.h"
#include "UDeviceType.h"

#include "UActuator.h"
#include "USwitchActuator.h"

#include "USensor.h"
#include "USensorLight.h"
#include "USensorTemperature.h"

class UActuator;
class USensor;
class UScenario;
class UTask;
class UCondition;

class UDeviceHandler {
private:
    int m_delayBetweenSensorPooling;
    int m_timeElapsed;
    int m_timeForNextSleep;

    void UpdateDelayBetweenReads();

    int m_SensorCount;
    int m_ActuatorCount;
    
    USensor** m_Sensors;
    UActuator** m_Actuators;

public:

    UDeviceHandler();
    virtual ~UDeviceHandler();

    bool AddDevice(UDevice* a_newDevice);
    bool DeleteDevice(UDevice* a_device);
    bool DeleteDevice(int a_deviceId);

    void StartPoolingSensors();
    bool AddNewSensor(UDevice* device, int a_pinUsed, int a_timeBetweenReads);
    bool DeleteSensor(int a_sensorId);

    bool AddNewActuator(UDevice* device, int a_pinUsed);
    bool DeleteActuator(int a_actuatorId);
    bool SetActuatorValue(int a_actuatorId, string a_value);

    void GetDeviceIds(int* returArray);

    USensor* GetSensor(int a_deviceId);
    UActuator* GetActuator(int a_deviceId);
    UDevice* GetDevice(int a_deviceId);
    UScenario* GetScenario(int a_scenarioId);
    UTask* GetTask(int a_taskId);
    UCondition* GetCondition(int a_conditionId);
    
    bool DeleteScenario(int a_scenarioId);
    bool DeleteTask(int a_taskId);
    bool DeleteCondition(int a_conditionId);

    void DeleteDevices();
    void DeleteScenarios(int a_deviceId);
    void DeleteTasks(int a_scenarioId);
    void DeleteConditions(int a_taskId);
    
    int GetSensorCount() { return m_SensorCount; }
    int GetActuatorCount() { return m_ActuatorCount; }
    int GetDeviceCount() { return m_SensorCount + m_ActuatorCount; }
    
    // Update the conditions related to said sensor
    int UpdateConditions(int a_SensorId, int a_Value); 

};

#endif /* UDEVICEHANDLER_H_ */


