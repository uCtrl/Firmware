#ifndef SENSORS_FAKESENSOR_H_
#define SENSORS_FAKESENSOR_H_

#include "FakeMessageHandler.h"
#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"

class FakeSensor
{
protected:
    char* m_sensorName;
    int m_timeBetweenReads;
    //static int s_threadId;

	RtosTimer m_timer;
    AnalogIn analogIn;

    FakeMessageHandler* m_messageHandler;

public:
    /*  Default constructor
    */
    FakeSensor();

    /*  Constructor with parameters
        @param a_name The sensor name
        @param a_pin The pin used to read the sensor
    */
    FakeSensor(FakeMessageHandler* messageHandler, char* a_name, int a_pin, int timeBetweenReads);

    // Forcefully reads a new value from the sensor, saves it in m_LastValueRead
    // and raises the m_NewValueAvailableFlag.
    void ForceNewValueRead();

    void Read();
    int ReadValue();

    // Save the current state of the sensor.
    void SaveState();

    char* GetName() { return m_sensorName; }

};

#endif  // SENSORS_FAKESENSOR_H_
