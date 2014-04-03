#ifndef SENSORS_FAKESENSOR_H_
#define SENSORS_FAKESENSOR_H_

#include "FakeMessageHandler.h"
#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include <string.h>

class FakeSensor
{
protected:
    Ticker ticker;
    AnalogIn analogIn;
    char* m_sensorName;

public:
    /*  Default constructor
    */
    FakeSensor();

    /*  Constructor with parameters
        @param a_name The sensor name
        @param a_pin The pin used to read the sensor
    */
    FakeSensor(char* a_name, int a_pin);

    // Forcefully reads a new value from the sensor, saves it in m_LastValueRead
    // and raises the m_NewValueAvailableFlag.
    virtual void ForceNewValueRead();

    virtual void Read();

    // Save the current state of the sensor.
    virtual void SaveState();

    char* GetName() { return m_sensorName; }

};

#endif  // SENSORS_FAKESENSOR_H_
