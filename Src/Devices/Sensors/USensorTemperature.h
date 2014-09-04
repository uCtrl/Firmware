#ifndef SENSORS_USENSORTEMPERATURE_H_
#define SENSORS_USENSORTEMPERATURE_H_

#include "FakeMessageHandler.h"
#include "defines.h"
#include "mbed.h"
#include "UPinUtils.h"
#include "rtos.h"
#include "USensor.h"

class USensorTemperature : public USensor
{
protected:

public:

	USensorTemperature(uint32_t a_id, uint32_t a_pin, uint32_t timeBetweenReads, char* a_sensorName);
    virtual ~USensorTemperature();
    virtual void Read();

};

#endif  // SENSORS_USENSORTEMPERATURE_H_
