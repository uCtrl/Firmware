#ifndef SENSORS_USENSORTEMPERATURE_H_
#define SENSORS_USENSORTEMPERATURE_H_

#include "FakeMessageHandler.h"
#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "USensor.h"
#include "UTaskHandler.h"
#include "UDevice.h"

class USensorTemperature : public USensor
{
protected:

public:

	USensorTemperature(UDevice* a_device, int a_pin, int timeBetweenReads);
    virtual ~USensorTemperature();
    virtual void Read();

};

#endif  // SENSORS_USENSORTEMPERATURE_H_
