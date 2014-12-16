#pragma once
#include "HostMessage.h"
#include "HostMessages.h"

class Network_Start_Request :	public HostMessage
{
private:
	NetworkStartRequest _NetworkStartRequest;
	void * GetHeader() { return & _NetworkStartRequest; }
	int GetMsgSize() { return sizeof(_NetworkStartRequest); }
	
public:
	Network_Start_Request(void);
	Network_Start_Request(BYTE * msg, int offset);
	Network_Start_Request(const Network_Start_Request & msg);

	virtual ~Network_Start_Request(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Network_Start_UID;}

	UINT16 Get_PAN_Id() { return _NetworkStartRequest._PAN_Id; }
	void Set_PAN_Id(UINT16 panId) { _NetworkStartRequest._PAN_Id = panId; }
};

class Network_Start_Confirm :	public HostMessage
{
private:
	NetworkStartConfirm _NetworkStartConfirm;
	void * GetHeader() { return & _NetworkStartConfirm; }
	int GetMsgSize() { return sizeof(_NetworkStartConfirm); }
	
public:
	Network_Start_Confirm(void);
	Network_Start_Confirm(BYTE * msg, int offset);
	Network_Start_Confirm(const Network_Start_Confirm & msg);

	virtual ~Network_Start_Confirm(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Network_Start_UID + 1;}

	UINT16 Get_Status() { return _NetworkStartConfirm._Status; }
	void Set_Status(UINT16 status) { _NetworkStartConfirm._Status = status; }
};
