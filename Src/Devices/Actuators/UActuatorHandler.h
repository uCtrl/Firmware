#ifndef ACTUATORS_UACTUATORHANDLER_H_
#define ACTUATORS_UACTUATORHANDLER_H_

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
    uint8_t m_ActuatorCount;
    FakeActuator* m_Actuators[ACTUATORS_LIST_LENGTH];

public:

    UActuatorHandler(); // Public Constructor

    bool AddNewActuator(UActuatorType a_type, uint8_t a_actuatorId, uint8_t a_pinUsed, char* a_actuatorName);
    bool DeleteActuator(uint8_t a_actuatorId);
    bool SetActuatorValue(char* a_actuatorName, uint8_t a_value);

    // Get all the names of the sensors
    char** GetActuatorNames();

    // Get the number of sensors
    uint8_t GetActuatorCount() { return m_ActuatorCount; }

};

#endif  // ACTUATORS_UACTUATORHANDLER_H_
