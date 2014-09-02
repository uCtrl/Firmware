#ifndef ACTUATOR_FAKEACTUATOR_H_
#define ACTUATOR_FAKEACTUATOR_H_

#include "FakeMessageHandler.h"
#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include <string.h>

class FakeActuator
{

protected:
    DigitalOut digitalOut;
    uint8_t m_actuatorId;
    char* m_actuatorName;

public:
    /*  Default constructor
    */
    FakeActuator();

    /*  Constructor with parameters
        @param a_name The sensor name
        @param a_pin The pin used to read the sensor
    */
    FakeActuator(uint8_t a_id, uint8_t a_pin, char* a_actuatorName);

    void SetValue(uint8_t a_value);

    int GetId() { return m_actuatorId; }

};

#endif  // ACTUATOR_FAKEACTUATOR_H_
