#pragma once
#include "HostMessages.h"
#include "HostMessage.h"

class Data_Transfer_Confirm :	public HostMessage
{
private:
	DataTransferConfirm _DTC;

	void * GetHeader() { return & _DTC; }
	int GetMsgSize() { return sizeof(DataTransferConfirm); }

public:


public:
	Data_Transfer_Confirm(void);
	Data_Transfer_Confirm(BYTE * msg, int offset);
	Data_Transfer_Confirm(const Data_Transfer_Confirm & msg);
	virtual ~Data_Transfer_Confirm(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Data_Transfer_UID_Confirm;}

	BYTE Get_NSDU()					{ return _DTC._NSDU_Handle; }
	BYTE Get_ConfirmFlag()	{ return _DTC._ConfirmFlag; }
	UINT16 Get_Status()			{return _DTC._Status; }
};
