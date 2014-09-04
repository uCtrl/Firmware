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
    uint32_t m_SensorCount;
    uint32_t m_delayBetweenSensorPooling;
    uint32_t m_timeElapsed;
    uint32_t m_timeForNextSleep;
    USensor* m_Sensors[SENSOR_LIST_LENGTH];

    void UpdateDelayBetweenReads();

public:

    USensorHandler();

    bool AddNewSensor(USensorType type, uint32_t a_sensorId, uint32_t a_pinUsed, uint32_t a_timeBetweenReads, char* a_sensorName);
    bool DeleteSensor(uint32_t a_sensorId);
    void StartPoolingSensors();

    // Get all the names of the sensors
    char** GetSensorNames();

    // Get the number of sensors
    uint32_t GetSensorCount() { return m_SensorCount; }

};

#endif  // SENSORS_USENSORHANDLER_H_
