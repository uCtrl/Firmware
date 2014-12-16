#pragma once
#include "HostMessage.h"
#include "HostMessages.h"


class Attach_Request :public HostMessage
{
private:
	AttachRequest _AttachRequest;
	void * GetHeader() { return & _AttachRequest; }
	int GetMsgSize() { return sizeof(AttachRequest); }

public:
	Attach_Request(void);
	Attach_Request(BYTE * msg, int offset);
	Attach_Request(const Attach_Request & msg);

	virtual ~Attach_Request(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Attach_UID_Request;}

	UINT16 Get_PAN_Id() { return _AttachRequest._PAN_Id; }
	UINT16 Get_LBA_Address() { return _AttachRequest._LBA_Address; }

	void Set_PAN_Id(UINT16 pan) { _AttachRequest._PAN_Id = pan; }
	void Set_LBA_Address(UINT16 lba) { _AttachRequest._PAN_Id = lba; }
};

class Attach_Confirm :public HostMessage
{
private:
	AttachConfirm _AttachConfirm;
	void * GetHeader() { return & _AttachConfirm; }
	int GetMsgSize() { return sizeof(AttachConfirm); }

public:
	Attach_Confirm(void);
	Attach_Confirm(BYTE * msg, int offset);
	Attach_Confirm(const Attach_Confirm & msg);

	virtual ~Attach_Confirm(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Attach_UID_Confirm;}

	UINT16 Get_Status() { return _AttachConfirm._Status; }
	UINT16 Get_NetworkAddress() { return _AttachConfirm._NetworkAddress; }
	UINT16 Get_PAN_Id() { return _AttachConfirm._PAN_Id; }
	
	void Set_Status(UINT16 status) { _AttachConfirm._Status = status; }
	void Set_PAN_Id(UINT16 pan) { _AttachConfirm._PAN_Id = pan; }
	void Set_NetworkAddress(UINT16 address) { _AttachConfirm._NetworkAddress = address; }
};

class Attach_Indication :public HostMessage
{
private:
	AttachIndication _AttachIndication;
	void * GetHeader() { return & _AttachIndication; }
	int GetMsgSize() { return sizeof(AttachIndication); }
	int ReadMessage(BYTE * msg, int offset);

public:
	Attach_Indication(void);
	Attach_Indication(BYTE * msg, int offset);
	Attach_Indication(const Attach_Indication & msg);

	virtual ~Attach_Indication(void);

	virtual int GetUniqueId() {return Attach_UID_Indication;}
	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();

	BYTE * Get_IPv6_Address() { return _AttachIndication._IPv6_Address; }
	BYTE * Get_ExtendedAddress() { return _AttachIndication._ExtendedAddress; }
	BYTE Get_CapabilityInfo() { return _AttachIndication._CapabilityInfo; }
};
