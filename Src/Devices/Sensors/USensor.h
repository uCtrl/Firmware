#ifndef SENSORS_USENSOR_H_
#define SENSORS_USENSOR_H_

#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "UDeviceType.h"

class UDevice;

class USensor
{
protected:
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
    USensor(UDevice* a_device, int a_pin, int a_timeBetweenReads);

    int ReadValue();
    virtual void Read();

    void SetTimeBetweenReads(int timeBetweenReads) { m_timeBetweenReads = timeBetweenReads; }
    int GetTimeBetweenReads() { return m_timeBetweenReads; }

    UDevice* Device;

};

#endif  // SENSORS_USENSOR_H_
