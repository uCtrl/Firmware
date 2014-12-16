#pragma once
#include "HostMessages.h"
#include "HostMessage.h"

class Data_Transfer_Request :	public HostMessage
{
private:
	DataTransferRequest * _pDTR;
	void * GetHeader() { return _pDTR; }
	int GetMsgSize();

	DataTransferRequest * Get_DTR_Pointer();
	static BYTE _NSDU;
	void SwapBytes();
	
	int ReadMessage(BYTE * data, int offset);

public:
	Data_Transfer_Request(void);
	Data_Transfer_Request(BYTE * msg, int offset);
	Data_Transfer_Request(Data_Transfer_Request & dtr);

	virtual ~Data_Transfer_Request(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Data_Transfer_UID_Request;}
	virtual void CopyTo(HostMessage * msg);
	virtual Message * MakeMessage();

	void Set_NSDU(BYTE nsdu);
	
	void Set_QOS_Flag(BYTE qos);
	void Set_SEC_Flag(BYTE sec);
	void Set_DiscoveryRoute_Flag(BYTE dr);

	void Set_Destination_Add(BYTE * add);
	void Set_Source_Add(BYTE * add);
	void Set_HopLimit(BYTE limit);

	void Set_SourcePort(UINT16 port);
	void Set_DestinationPort(UINT16 port);
	
	void Set_Data(int length, BYTE * data);
	Message * Get_Data();

	BYTE Get_NSDU();
	
	BYTE Get_QOS_Flag();
	BYTE Get_SEC_Flag();
	BYTE Get_DiscoveryRoute_Flag();

	BYTE * Get_Destination_Add();
	BYTE * Get_Source_Add();
	UINT8 Get_HopLimit();

	UINT16 Get_SourcePort();
	UINT16 Get_DestinationPort();
	UINT16 Get_UDP_Length();
	UINT16 Get_CRC();
};

