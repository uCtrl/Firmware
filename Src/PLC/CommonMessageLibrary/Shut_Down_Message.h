#pragma once
#include "Status_Message.h"
#include "MessageIds.h"
#include "HostMessages.h"

class Shut_Down_Message :	public HostMessage
{
private: 
	ShutDownMessage _ShutDownMessage;
	void * GetHeader() { return & _ShutDownMessage; }
	int GetMsgSize() { return sizeof(ShutDownMessage); }

public:
	Shut_Down_Message(void);
	Shut_Down_Message(BYTE * data, int offset);
	Shut_Down_Message(const Shut_Down_Message & msg);

	virtual ~Shut_Down_Message(void);

	virtual void InitializeData();
	virtual TextString ToString();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual int GetUniqueId(){ return Shut_Down_UID; }

	void SetResetType(ResetType type) { _ShutDownMessage._ResetType = (UINT16) type; }
	ResetType GetResetType() { return (ResetType)_ShutDownMessage._ResetType; }
};

