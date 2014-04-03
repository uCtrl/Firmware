#ifndef SENSORS_USENSORHANDLER_H_
#define SENSORS_USENSORHANDLER_H_

class FakeSensor;

#include "FakeSensor.h" // Todo : delete
#include "USensorType.h"
#include "string.h"
#include "defines.h"

// Contains the list of all the sensors, and do the necessary operations
// to add, remove, or modify a sensor
class USensorHandler
{
private:
    int m_SensorCount;
    FakeSensor* m_Sensors[SENSOR_LIST_LENGTH];

    static bool instanceFlag;
    static USensorHandler *instance;

    USensorHandler(); // Private Constructor

public:

    static USensorHandler* GetInstance();

    bool AddNewSensor(USensorType type, char* sensorName, int pinUsed);
    bool DeleteSensor(char* sensorName);

    // Get all the names of the sensors
    char** GetSensorNames();

    // Get the number of sensors
    int GetSensorCount() { return m_SensorCount; }

};

#endif  // SENSORS_USENSORHANDLER_H_
