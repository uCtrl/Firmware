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
    char* m_actuatorName;

public:
    /*  Default constructor
    */
    FakeActuator();

    /*  Constructor with parameters
        @param a_name The sensor name
        @param a_pin The pin used to read the sensor
    */
    FakeActuator(char* a_name, int a_pin);

    void SetValue(int a_value);

    char* GetName() { return m_actuatorName; }

};

#endif  // ACTUATOR_FAKEACTUATOR_H_
