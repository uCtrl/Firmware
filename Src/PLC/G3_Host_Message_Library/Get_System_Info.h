#pragma once

#include "../CommonMessageLibrary/HostMessage.h"
//#include "../UtilityLibrary/CallBackList.h"
#include "../SharedHostMessageLibrary/HostMessages.h"

class Get_System_Info_Request :	public HostMessage
{
private:
	GetSystemInfoRequest _GetSystemInfoRequest;

	void * GetHeader() { return & _GetSystemInfoRequest; }
	int GetMsgSize() { return sizeof(GetSystemInfoRequest); }
public:
	Get_System_Info_Request(void);
	Get_System_Info_Request(BYTE * msg, int offset);
	Get_System_Info_Request(const Get_System_Info_Request & msg);

	virtual ~Get_System_Info_Request(void);

	virtual int GetUniqueId() {return Get_System_Info_UID + 0;}
	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
};

class Get_System_Info : public HostMessage
{
private:
	SystemInfo _SystemInfo;

	void * GetHeader() { return & _SystemInfo; }
	int GetMsgSize() { return sizeof(SystemInfo); }

public: 
	Get_System_Info(void);
	Get_System_Info(BYTE * msg, int offset);
	Get_System_Info(const Get_System_Info & msg);

	virtual ~Get_System_Info(void);

	virtual void InitializeData();
	virtual TextString ToString();
	virtual	HostMessage * CreateMessage(BYTE * data, int offset);
	virtual int GetUniqueId() {return Get_System_Info_UID + 1;}

//	static UINT32  DSP_Version;

public:
	/*
	UINT16 _MAC_RX_Max_Hold_PPDU;
	UINT16 _PRIME_MAC_Max_Conns;
	UINT16 _MAC_Max_RX_Q_Length;
	BYTE _Flag1;
	BYTE _SecurityProfile;

	UINT16 _AddressType;
	BYTE _LongAddress[8];
	UINT16 _PanId;
	UINT16 _ShortAddress;
	UINT16 _SegmentLength;

	*/
	BYTE Get_Build() { return _SystemInfo._Build; }
	BYTE Get_Revision() { return _SystemInfo._Revision; }
	BYTE Get_Minor() { return _SystemInfo._Minor; }
	BYTE Get_Major() { return _SystemInfo._Major; }

//	UINT16 Get_SerialNumberLength() { return _SystemInfo._SerialNumberLength; }
//	BYTE * Get_SerialNumber() { return _SystemInfo._SerialNumber; }
	BYTE Get_DeviceType() { return _SystemInfo._DeviceType; }
	BYTE Get_DeviceMode() { return _SystemInfo._DeviceMode; }
	UINT16 Get_HardwareRevision() { return _SystemInfo._HardwareRevision; }
//	BYTE * Get_EUI() { return _SystemInfo._EUI; }
	BYTE Get_Diag_Port() { return ((_SystemInfo._PortAssigments & 0x0C) >> 2); }
	BYTE Get_Data_Port() { return (_SystemInfo._PortAssigments & 0x03); }
//	UINT16 Get_MAC_RX_Max_Hold_PPDU(){return _SystemInfo._MAC_RX_Max_Hold_PPDU; }
//	UINT16 Get_PRIME_MAC_Max_Conns() { return _SystemInfo._PRIME_MAC_Max_Conns; }
//	UINT16 Get_MAC_Max_RX_Q_Length() { return _SystemInfo._MAC_Max_RX_Q_Length; }
//	BYTE Get_SecurityProfile() { return _SystemInfo._SecurityProfile; }
//	UINT16 Get_AddressType() { return _SystemInfo._AddressType; }
	BYTE * Get_LongAddress() { return _SystemInfo._LongAddress; }
//	UINT16 Get_PAN_Id() { return _SystemInfo._PanId; }
//	UINT16 Get_ShortAddress() { return _SystemInfo._ShortAddress; }
//	UINT16 Get_SegmentLength() { return _SystemInfo._SegmentLength; }

//	BYTE Get_ApplyFlag();
//	void Set_ApplyFlag(BYTE flag);

//	BYTE Get_IP_Flag();
//	void Set_IP_Flag(BYTE flag);

//	BYTE GetAutoMode();
//	void SetAutoMode(BYTE flag);

	BYTE Get_COH_Flag();
	void Set_COH_Flag(BYTE flag);
	BYTE Get_TMR_Flag();
	void Set_TMR_Flag(BYTE flag);

//	BYTE Get_PAN_Coord_Flag();
//	void Set_PAN_Coord_Flag(BYTE flag);

//	BYTE Get_MAC_ARQ_Flag();
//	void Set_MAC_ARQ_Flag(BYTE flag);

//	BYTE Get_MAC_PAC_Flag();
//	void Set_MAC_PAC_Flag(BYTE flag);
};