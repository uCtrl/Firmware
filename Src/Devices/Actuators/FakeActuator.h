#ifndef ACTUATOR_FAKEACTUATOR_H_
#define ACTUATOR_FAKEACTUATOR_H_

#include "FakeMessageHandler.h"
#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include <string.h>
#include "UDevice.h"

class UDevice;

class FakeActuator
{

protected:
    DigitalOut digitalOut;
    int m_actuatorId;
    char* m_actuatorName;

public:
    /*  Default constructor
    */
    FakeActuator();

    /*  Constructor with parameters
        @param a_name The sensor name
        @param a_pin The pin used to read the sensor
    */
    FakeActuator(UDevice* device, int a_pin);

    void SetValue(int a_value);

    int GetId() { return m_actuatorId; }

    UDevice* Device;

};

#endif  // ACTUATOR_FAKEACTUATOR_H_
