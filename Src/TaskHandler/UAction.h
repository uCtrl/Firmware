#ifndef UACTION_H_
#define UACTION_H_

#include <stdint.h>
#include "TaskHandlerConfigFile.h"

class UAction
{
public:
	UAction();
	UAction(uint32_t mActionID, uint32_t mActuatorID, uint32_t mNewValue, uint8_t mActionName[ACTION_NAME_LENGHT]);
	virtual ~UAction();
	virtual uint32_t SetValue();

	uint32_t ActionID;
	uint32_t ActuatorID;
	uint32_t NewValue;
	uint8_t ActionName[ACTION_NAME_LENGHT];
};

#endif //UACTION_H_

