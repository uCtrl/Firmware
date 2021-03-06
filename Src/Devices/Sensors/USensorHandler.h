#ifndef SENSORS_USENSORHANDLER_H_
#define SENSORS_USENSORHANDLER_H_

//class USensor;
//class USensorLight;
//class USensorTemperature;
//class FakeMessageHandler;

#include "USensor.h"
#include "USensorLight.h"
#include "USensorTemperature.h"
#include "USensorType.h"
#include "string.h"
#include "defines.h"
#include "UMathUtils.h"

// Create a real time clock sensor
// Abstract class RTC, with implementations, Day Sensor, Week Sensor, Month, Year, Hour, Minute, Seconds

// Contains the list of all the sensors, and do the necessary operations
// to add, remove, or modify a sensor
class USensorHandler
{
private:
    int m_SensorCount;
    int m_delayBetweenSensorPooling;
    int m_timeElapsed;
    int m_timeForNextSleep;
    USensor* m_Sensors[SENSOR_LIST_LENGTH];

    void UpdateDelayBetweenReads();

public:

    USensorHandler();

    bool AddNewSensor(USensorType type, int a_sensorId, int a_pinUsed, int a_timeBetweenReads, char* a_sensorName);
    bool DeleteSensor(int a_sensorId);
    void StartPoolingSensors();

    // Get all the names of the sensors
    char** GetSensorNames();

    // Get the number of sensors
    int GetSensorCount() { return m_SensorCount; }

};

#endif  // SENSORS_USENSORHANDLER_H_
