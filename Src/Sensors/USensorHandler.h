#ifndef SENSORS_USENSORHANDLER_H_
#define SENSORS_USENSORHANDLER_H_

class FakeSensor;
class FakeMessageHandler;

#include "FakeSensor.h" // Todo : replace with real sensors
#include "USensorType.h"
#include "FakeMessageHandler.h"
#include "string.h"
#include "defines.h"

// Create a real time clock sensor
// Abstract class RTC, with implementations, Day Sensor, Week Sensor, Month, Year, Hour, Minute, Seconds

// Contains the list of all the sensors, and do the necessary operations
// to add, remove, or modify a sensor
class USensorHandler
{
private:
    int m_SensorCount;
    FakeSensor* m_Sensors[SENSOR_LIST_LENGTH];
    FakeMessageHandler* m_messageHandler;

public:

    USensorHandler(FakeMessageHandler*);

    bool AddNewSensor(USensorType type, char* sensorName, int pinUsed);
    bool DeleteSensor(char* sensorName);

    // Get all the names of the sensors
    char** GetSensorNames();

    // Get the number of sensors
    int GetSensorCount() { return m_SensorCount; }

};

#endif  // SENSORS_USENSORHANDLER_H_
