#ifndef SENSORS_USENSORTEMPERATURE_H_
#define SENSORS_USENSORTEMPERATURE_H_

#include "cfg.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "USensor.h"
#include "UTaskHandler.h"

class USensorTemperature : public USensor
{
protected:
    AnalogIn analogIn;

public:
	USensorTemperature(UDevice* a_device, int a_pin, int timeBetweenReads);
    virtual ~USensorTemperature();
    virtual void Read();

};

#endif  // SENSORS_USENSORTEMPERATURE_H_

