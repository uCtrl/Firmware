#ifndef SENSORS_USENSORLIGHT_H_
#define SENSORS_USENSORLIGHT_H_

#include "FakeMessageHandler.h"
#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "USensor.h"

class USensorLight : public USensor
{
protected:
    int m_lightSensorBuffer[10] = {0};
    int m_lightSensorCount;

public:

    USensorLight(FakeMessageHandler* messageHandler, int a_id, int a_pin, int timeBetweenReads);
    virtual ~USensorLight();
    virtual void Read();

};

#endif  // SENSORS_USENSORLIGHT_H_
