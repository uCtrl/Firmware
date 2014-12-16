#ifndef SENSORS_USENSORLIGHT_H_
#define SENSORS_USENSORLIGHT_H_

#include "cfg.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "USensor.h"
#include "UDevice.h"

class USensorLight : public USensor
{

public:
    USensorLight(UDevice* device, int a_pin, int a_timeBetweenReads);
    virtual ~USensorLight();
    
    virtual int ReadValue();
    virtual void Read();

protected:
    int m_lightSensorCount;
    AnalogIn analogIn;

};

#endif  // SENSORS_USENSORLIGHT_H_

