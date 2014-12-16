#pragma once
#include "HostMessages.h"
#include "HostMessage.h"
#include "WordArray.h"

class Alarm : public HostMessage
{
private: 
	NetworkStatusAlarm * _pNSA;
	void * GetHeader() { return _pNSA; }
	int GetMsgSize();

public:
	Alarm(void);
	Alarm(BYTE *msg, int offset);
	Alarm(Alarm & alarm);

	virtual ~Alarm(void);
	
	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual int ReadMessage(BYTE * data, int offset);
	virtual TextString ToString();
	
	virtual int GetUniqueId() { return Alarm_UID; }
	virtual void CopyTo(HostMessage * msg);
	virtual Message * MakeMessage();
	UINT16 GetAlarmId();
	UINT16 GetStatus();
	BYTE GetSecurityLevel();
	BYTE GetKeyIdMode();
	UINT16 GetKeyIndex();

	UINT16 GetPanId();
	UINT16 GetAddressMode();
	WordArray GetAddress();
};

