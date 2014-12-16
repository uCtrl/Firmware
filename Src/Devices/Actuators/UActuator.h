
#ifndef ACTUATOR_UACTUATOR_H_
#define ACTUATOR_UACTUATOR_H_

#include "cfg.h"
#include "mbed.h"
#include "UPinUtils.h"
#include <string.h>
#include "UDevice.h"

class UDevice;

class UActuator
{
public:
    UActuator();
    virtual ~UActuator();
    
    UActuator(UDevice* device);

    virtual void SetValue(string a_value);

    UDevice* Device;
};

#endif  // ACTUATOR_UACTUATOR_H_

