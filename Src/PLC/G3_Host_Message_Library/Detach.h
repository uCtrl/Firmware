#pragma once
#include "HostMessages.h"
#include "HostMessage.h"

class Detach_Request :	public HostMessage
{
private:

	DetachRequest _DetachRequest;
	void * GetHeader() { return & _DetachRequest; }
	int GetMsgSize() { return sizeof(DetachRequest); }

public: 

public:
	Detach_Request(void);
	Detach_Request(BYTE * msg, int offset);
	Detach_Request(const Detach_Request & msg);

	virtual ~Detach_Request(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Detach_UID_Request;}

	BYTE * Get_ExtendedAddress() { return _DetachRequest._ExtendedAddress; }
	void Set_ExtendedAddress( BYTE * address);
};

class Detach_Confirm :	public HostMessage
{
private:
	DetachConfirm _DetachConfirm;
	void * GetHeader() { return & _DetachConfirm; }
	int GetMsgSize() { return sizeof(DetachConfirm); }

public:
	Detach_Confirm(void);

	Detach_Confirm(int size, BYTE * msg, int offset);
	Detach_Confirm(BYTE * msg, int offset);
	Detach_Confirm(Message * msg, int offset);

	Detach_Confirm(const Detach_Confirm & msg);

	virtual ~Detach_Confirm(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Detach_UID_Confirm;}

	UINT16 Get_Status() { return _DetachConfirm._Status; }
	BYTE * Get_ExtendedAddress() { return _DetachConfirm._ExtendedAddress; }

	void Set_Status(UINT16 status) { _DetachConfirm._Status = status; }
	void Set_ExtendedAddress( BYTE * address);
};

class Detach_Indication :	public HostMessage
{
private:

	DetachIndication _DetachIndication;
	void * GetHeader() { return & _DetachIndication; }
	int GetMsgSize() { return sizeof(Detach_Indication); }

public: 

public:
	Detach_Indication(void);
	Detach_Indication(BYTE * msg, int offset);
	Detach_Indication(const Detach_Indication & msg);

	virtual ~Detach_Indication(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Detach_UID_Indication;}

	BYTE * Get_ExtendedAddress() { return _DetachIndication._ExtendedAddress; }
	void Set_ExtendedAddress( BYTE * address);
};
