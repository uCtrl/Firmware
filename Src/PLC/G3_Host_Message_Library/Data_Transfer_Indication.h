#pragma once
#include "HostMessages.h"
#include "HostMessage.h"

class Data_Transfer_Indication :	public HostMessage
{
private:
	DataTransferIndication * _pDTI;
	void * GetHeader() { return _pDTI; }
	int GetMsgSize();

	DataTransferIndication * Get_DTI_Pointer();
	virtual Message * MakeMessage();
	
	void SwapBytes();
	int ReadMessage(BYTE * data, int offset);

public:
	Data_Transfer_Indication(void);
	Data_Transfer_Indication(BYTE * msg, int offset);
	Data_Transfer_Indication(Data_Transfer_Indication & dti);

	virtual ~Data_Transfer_Indication(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	TextString ToString();
	virtual int GetUniqueId() {return Data_Transfer_UID_Indication;}
	virtual void CopyTo(HostMessage * msg);
	//
	// This message is created by the PLC
	// Do not need set accessors.
	//
	Message * Get_Data();

	BYTE Get_LQI();
	BYTE Get_Confirmation_Flag();
	BYTE Get_SEC_Flag();

	BYTE * Get_Destination_Add();
	BYTE * Get_Source_Add();
	UINT8 Get_HopLimit();

	UINT16 Get_SourcePort();
	UINT16 Get_DestinationPort();
	UINT16 Get_UDP_Length();
	UINT16 Get_CRC();
};
