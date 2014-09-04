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
	uint32_t m_sensorId;
    uint32_t m_timeBetweenReads;

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
    USensor(uint32_t a_id, uint32_t a_pin, uint32_t a_timeBetweenReads, char* a_deviceName);

    virtual void Read();
    uint32_t ReadValue();

    // Save the current state of the sensor.
    void SaveState();

    void SetTimeBetweenReads(uint32_t timeBetweenReads) { m_timeBetweenReads = timeBetweenReads; }
    uint32_t GetTimeBetweenReads() { return m_timeBetweenReads; }

    uint32_t GetId() { return m_sensorId; }

};

#endif  // SENSORS_USENSOR_H_
