#pragma once

#include "MessageHeader.h"
#include "MessageIds.h"
#include "../UtilityLibrary/Message.h"

//#define P1901
#define G3

class HostMessage
{
protected:
	virtual void * GetHeader() = 0;
	virtual int GetMsgSize() = 0;
	
public:
	HostMessage(void){};

	virtual ~HostMessage(void){};

	virtual void SetId(BYTE id);
	virtual void SetORG(BYTE origin);
	virtual void SetRPY(BYTE rpy);
	virtual void SetSEQ(BYTE seq);
	virtual BYTE GetId();
	virtual UINT16 GetLength();
	virtual BYTE GetORG();
	virtual BYTE GetRPY();
	virtual BYTE GetSEQ();

	virtual int GetKey() { return (GetId() << 8 )+ (GetORG() & 0x80); }

	virtual int ReadMessage(BYTE * data, int offset);
	virtual Message * MakeMessage();
	virtual void CopyTo(HostMessage * msg);	

	virtual int GetUniqueId() = 0;
	virtual void InitializeData() = 0;
	virtual TextString ToString() = 0;
	virtual HostMessage * CreateMessage(BYTE * data, int offset) = 0;	
};