#ifndef SENSORS_FAKESENSOR_H_
#define SENSORS_FAKESENSOR_H_

#include "FakeMessageHandler.h"
#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"

class USensor
{
protected:
    int m_sensorId;
    int m_timeBetweenReads;
    //static int s_threadId;
	//RtosTimer m_timer;

    AnalogIn analogIn;

    FakeMessageHandler* m_messageHandler;

public:
    /*  Default constructor
    */
    USensor();

    virtual ~USensor();

    /*  Constructor with parameters
        @param a_name The sensor name
        @param a_pin The pin used to read the sensor
    */
    USensor(FakeMessageHandler* messageHandler, int a_id, int a_pin, int timeBetweenReads);

    virtual void Read();
    int ReadValue();

    // Save the current state of the sensor.
    void SaveState();

    void SetTimeBetweenReads(int timeBetweenReads) { m_timeBetweenReads = timeBetweenReads; }
    int GetTimeBetweenReads() { return m_timeBetweenReads; }

    int GetId() { return m_sensorId; }

};

#endif  // SENSORS_FAKESENSOR_H_
