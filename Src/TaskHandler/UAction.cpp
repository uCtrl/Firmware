#include "UAction.h"


UAction::UAction()
{
	ActionID = 0;
	ActuatorID = 0;
	NewValue = 0;
	for(uint8_t i = 0; i < ACTION_NAME_LENGHT; i++)
	{
		ActionName[i] = 0;
	}
}

UAction::UAction(uint32_t mActionID, uint32_t mActuatorID, uint32_t mNewValue, uint8_t mActionName[ACTION_NAME_LENGHT])
{
	ActionID = mActionID;
	//*ActionName = *mActionName;
	for(uint8_t i = 0; i < ACTION_NAME_LENGHT; i++)
	{
		ActionName[i] = mActionName[i];
	}
	ActuatorID = mActuatorID;
	NewValue = mNewValue;
}

UAction::~UAction()
{
}


uint32_t UAction::SetValue()
{
	return 0;
}
