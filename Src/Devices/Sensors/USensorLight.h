#ifndef SENSORS_USENSORLIGHT_H_
#define SENSORS_USENSORLIGHT_H_

#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "USensor.h"
#include "UTaskRequest.h"
#include "UTaskHandler.h"
#include "UDevice.h"

const int LIGHT_SENSOR_BUFFER_SIZE = 10;

class USensorLight : public USensor
{

public:
    USensorLight(UDevice* device, int a_pin, int a_timeBetweenReads);
    virtual ~USensorLight();
    virtual void Read();

protected:
    int m_lightSensorBuffer[LIGHT_SENSOR_BUFFER_SIZE];
    int m_lightSensorCount;

};

#endif  // SENSORS_USENSORLIGHT_H_
