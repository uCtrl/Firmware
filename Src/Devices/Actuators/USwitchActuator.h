#ifndef ACTUATOR_ULEDACTUATOR_H_
#define ACTUATOR_ULEDACTUATOR_H_

#include "cfg.h"
#include "mbed.h"
#include "UPinUtils.h"
#include <string.h>
#include "UDevice.h"
#include "UActuator.h"

class UDevice;

class USwitchActuator : public UActuator
{

protected:
    DigitalOut digitalOut;
    int m_actuatorId;
    char* m_actuatorName;

public:
    /*  Default constructor
    */
    USwitchActuator();
    virtual ~USwitchActuator() {}

    /*  Constructor with parameters
        @param a_name The sensor name
        @param a_pin The pin used to read the sensor
    */
    USwitchActuator(UDevice* device, int a_pin);

    virtual void SetValue(string a_value);

};

#endif  // ACTUATOR_ULEDACTUATOR_H_

