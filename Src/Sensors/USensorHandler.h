#ifndef SENSORS_USENSORHANDLER_H_
#define SENSORS_USENSORHANDLER_H_

//class USensor;
//class USensorLight;
//class USensorTemperature;
class FakeMessageHandler;

#include "USensor.h"
#include "USensorLight.h"
#include "USensorTemperature.h"
#include "USensorType.h"
#include "FakeMessageHandler.h"
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
    uint32_t m_timeElapsed;
    int m_timeForNextSleep;
    USensor* m_Sensors[SENSOR_LIST_LENGTH];
    FakeMessageHandler* m_messageHandler;

    void UpdateDelayBetweenReads();

public:

    USensorHandler(FakeMessageHandler*);

    bool AddNewSensor(USensorType type, int sensorId, int pinUsed, int timeBetweenReads);
    bool DeleteSensor(int sensorId);
    void StartPoolingSensors();

    // Get all the names of the sensors
    char** GetSensorNames();

    // Get the number of sensors
    int GetSensorCount() { return m_SensorCount; }

};

#endif  // SENSORS_USENSORHANDLER_H_
