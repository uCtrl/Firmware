#pragma once
#include "HostMessages.h"
#include "HostMessage.h"
//#include "..\CommonMessageLibrary\tlv.h"
#include "MessageIds.h"
#include "Message.h"
#include "UPlcConfigFile.h"

class Load_System_Config :public HostMessage
{
private:
	LoadSystemConfig _Configuration;
	void * GetHeader() { return & _Configuration; }
	int GetMsgSize();
	//
	// These member function allways return a good pointer to the structs
	//
	PortDesignation * Get_PortDesignation();
	SystemConfig * Get_SystemConfg();
	G3Configuration * Get_G3Config();
	
public:
	Load_System_Config(void);
	Load_System_Config(BYTE * data, int offset);
	Load_System_Config(const Load_System_Config & msg);

	virtual ~Load_System_Config(void);

	virtual void InitializeData();
	virtual TextString ToString();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual int GetUniqueId() {return Get_System_Info_UID + 1;}
	virtual void CopyTo(HostMessage *msg );
	virtual Message * MakeMessage();

	//
	// Port Designation accessors
	//
	BYTE Get_DataPort();
	BYTE Get_DiagPort();
	void Set_DataPort(BYTE value);
	void Set_DiagPort(BYTE value);
	//
	// System config accessors.
	//
	//UINT16 Get_SerialNumberLength();
	//BYTE * Get_SerialNumber();
	//BYTE * Get_EUI();
	BYTE Get_DeviceMode();
	//BYTE Get_RPY_Flag();
	//BYTE Get_Auto_Flag();

	//void Set_SerialNumberLength(UINT16 value);
	//void Set_SerialNumber(BYTE * value);
	//void Set_EUI(BYTE * value);
	void Set_DeviceMode(BYTE value);
	//void Set_RPY_Flag(BYTE value);
	//void Set_Auto_Flag(BYTE value);
	//
	// G3 Config accessors
	//
	//BYTE Get_PAN_Coord_Flag();
	BYTE * Get_LongAddress();
	//UINT16 Get_PAN_Id();
	//UINT16 Get_ShortAddress();
	//UINT16 Get_MAC_SegmentSize();

	//void Set_PAN_Coord_Flag(BYTE value);
	void Set_LongAddress(BYTE * value);
	//void Set_PAN_Id(UINT16 value);
	//void Set_ShortAddress(UINT16 value);
	//void Set_MAC_SegmentSize(UINT16 value);
};

