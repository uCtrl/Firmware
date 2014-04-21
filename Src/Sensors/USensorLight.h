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

    USensorLight(FakeMessageHandler* messageHandler, char* a_name, int a_pin, int timeBetweenReads);
    virtual void Read();

};

#endif  // SENSORS_USENSORLIGHT_H_
