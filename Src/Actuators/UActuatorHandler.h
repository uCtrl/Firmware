#ifndef ACTUATORS_UACTUATORHANDLER_H_
#define ACTUATORS_UACTUATORHANDLER_H_

class FakeActuator;
class FakeMessageHandler;

#include "FakeActuator.h" // Todo : replace with real actuators
#include "UActuatorType.h"
#include "FakeMessageHandler.h"
#include "string.h"
#include "defines.h"

// Contains the list of all the sensors, and do the necessary operations
// to add, remove, or modify a sensor
class UActuatorHandler
{
private:
    int m_ActuatorCount;
    FakeActuator* m_Actuators[ACTUATORS_LIST_LENGTH];
    FakeMessageHandler* m_messageHandler;

public:

    UActuatorHandler(FakeMessageHandler*); // Public Constructor

    bool AddNewActuator(UActuatorType a_type, char* a_actuatorName, int a_pinUsed);
    bool DeleteActuator(char* a_actuatorName);
    bool SetActuatorValue(char* a_actuatorName, int a_value);

    // Get all the names of the sensors
    char** GetActuatorNames();

    // Get the number of sensors
    int GetActuatorCount() { return m_ActuatorCount; }

};

#endif  // ACTUATORS_UACTUATORHANDLER_H_
