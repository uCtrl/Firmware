#ifndef SENSORS_USENSORLIGHT_H_
#define SENSORS_USENSORLIGHT_H_

#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "USensor.h"
#include "UTaskRequest.h"
#include "UTaskHandler.h"

const uint32_t LIGHT_SENSOR_BUFFER_SIZE = 10;

class USensorLight : public USensor
{

public:
    USensorLight(uint32_t a_id, uint32_t a_pin, uint32_t a_timeBetweenReads, char* a_sensorName);
    virtual ~USensorLight();
    virtual void Read();

protected:
    uint32_t m_lightSensorBuffer[LIGHT_SENSOR_BUFFER_SIZE];
    uint32_t m_lightSensorCount;

};

#endif  // SENSORS_USENSORLIGHT_H_
