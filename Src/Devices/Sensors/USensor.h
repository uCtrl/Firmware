#ifndef SENSORS_USENSOR_H_
#define SENSORS_USENSOR_H_

#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "UDevice.h"

class UDevice;

class USensor : public UDevice
{
protected:
	int m_sensorId;
    int m_timeBetweenReads;

    AnalogIn analogIn;

public:
    /*  Default constructor
    */
    USensor();

    virtual ~USensor();

    /*  Constructor with parameters
        @param a_name The sensor name
        @param a_pin The pin used to read the sensor
    */
    USensor(int a_id, int a_pin, int a_timeBetweenReads, char* a_deviceName);

    virtual void Read();
    int ReadValue();

    void SetTimeBetweenReads(int timeBetweenReads) { m_timeBetweenReads = timeBetweenReads; }
    int GetTimeBetweenReads() { return m_timeBetweenReads; }

    int GetId() { return m_sensorId; }

};

#endif  // SENSORS_USENSOR_H_
