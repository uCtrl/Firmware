#pragma once
#include "HostMessage.h"
#include "HostMessages.h"

class Status_Message :	public HostMessage
{
private:
	StatusMessage _StatusMessage;
	void * GetHeader() { return & _StatusMessage; }
	int GetMsgSize() { return sizeof(StatusMessage); }

public:
	Status_Message(void);
	Status_Message(BYTE id);
	Status_Message(BYTE * msg, int offset);
	Status_Message(const Status_Message & msg);

	virtual ~Status_Message(void);


	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId(){ return 0; }

	UINT16 GetStatus() { return _StatusMessage._Status; }
};
