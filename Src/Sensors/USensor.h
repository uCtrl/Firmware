#ifndef SENSORS_USENSOR_H_
#define SENSORS_USENSOR_H_

#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "UTaskHandler.h"
#include "UTaskCfg.h"

extern Semaphore semMailUTaskHandler;
extern Mail<UTaskRequest, MAIL_LEN_UTASKHANDLER>mailUTaskHandler;

class USensor
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
    USensor(int a_id, int a_pin, int timeBetweenReads);

    virtual void Read();
    int ReadValue();

    // Save the current state of the sensor.
    void SaveState();

    void SetTimeBetweenReads(int timeBetweenReads) { m_timeBetweenReads = timeBetweenReads; }
    int GetTimeBetweenReads() { return m_timeBetweenReads; }

    int GetId() { return m_sensorId; }

};

#endif  // SENSORS_USENSOR_H_
