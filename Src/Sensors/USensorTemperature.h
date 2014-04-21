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

	USensorTemperature(FakeMessageHandler* messageHandler, char* a_name, int a_pin, int timeBetweenReads);
    virtual void Read();

};

#endif  // SENSORS_USENSORTEMPERATURE_H_
