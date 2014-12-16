#pragma once
#include "UPlcConfigFile.h"
//#pragma warning( push )
//#pragma pack( 1 )
//#pragma warning( disable : 4200 )

/*
===============================================================================

	Calculates a checksum for a block of data
	using the CCITT standard CRC-16.

===============================================================================
*/

unsigned short CRC16_InitChecksum();
unsigned short CRC16_UpdateChecksum(unsigned short crcvalue, const void *data, int length );
unsigned short CRC16_BlockChecksum( const void *data, int length );


enum MessageIds
{
	Data_Transfer_Id = 0x00,
	Get_System_Info_Id = 0x01,
	Get_PHY_PIB_Id = 0x02,
	Get_MAC_PIB_Id = 0x03,
	Set_Info_Id = 0x04,
	Shut_Down_Id = 0x05,
	Setup_Alarm_Id = 0x06,
	Alarm_Id = 0x07,
	Network_Register_Id = 0x08,
	Network_Start_Id = 0x08,
	Network_Unregister_Id = 0x09,
	Connect_Id = 0x0A,
	Disconnect_Id = 0x0B, 
	Load_System_Config_Id = 0x0C,
	Set_MAC_PIB_Id = 0x0D,
	Clear_PHY_PIB_Id = 0x0E,
	Clear_MAC_PIB_Id = 0x0F,
	Attach_Id = 0x10,
	Detach_Id = 0x11,
	Discover_Id = 0x12,
	Firmware_UpGrade_Id = 0x13
};

struct Header
{
	BYTE _Id;
	BYTE _Origin;
	UINT16 _Length;
};

struct CRC_Header
{
	UINT16 _HeaderCRC;
	UINT16 _MessageCRC;
};
struct IPv6
{
	BYTE   _Header[4];
	UINT16 _PayloadLength;  // = UPD Length 
	UINT8  _NextHeader;			// = 17 - udp message
	UINT8  _HopLimit;

	BYTE   _SourceAddress[16];
	BYTE   _DestinationAddress[16];
};

// variable length struct
struct UDP
{
	UINT16 _SourcePort;
	UINT16 _DestinationPort;
	UINT16 _Length;   // includes data and this header, min size is 8.
	UINT16 _CRC;			// aways set to zero for now
	BYTE  _Data[];
};

// variable length struct
struct NetworkStatusAlarm
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	UINT16 _TLV_Id;
	UINT16 _TLV_Length;
	BYTE _Data[];
};

struct DataTransferRequest
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	BYTE _NSDU_Handle;
	BYTE _Flags;
	//BYTE _L_SDU_Data[1];
	struct IPv6 _IPv6_Header;
	struct UDP _UDP_Message;
};

struct DataTransferConfirm
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	BYTE _NSDU_Handle;
	BYTE _ConfirmFlag;
	UINT16 _Status;
};

struct DataTransferIndication
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	BYTE _LQI;
	BYTE _Flags;
	//BYTE Data Payload[1];
	struct IPv6 _IPv6_Header;
	struct UDP _UDP_Message;
};

struct DataTransfer
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	UINT16 _Spacer;

	struct IPv6 _IPv6_Header;
	struct UDP _UDP_Message;
};


struct StatusMessage
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	UINT16 _Status;
};

struct ShutDownMessage
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	UINT16 _ResetType;
};

struct GetSystemInfoRequest
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
};

struct SystemInfo
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	BYTE _Build;
	BYTE _Revision;
	BYTE _Minor;
	BYTE _Major;

	BYTE _Reserved_0[18];
///	BYTE _SerialNumber[16];
	BYTE _DeviceType;
	BYTE _DeviceMode;
	UINT16 _HardwareRevision;
//	BYTE _EUI[6];
	BYTE Reserved_1[6];
	BYTE _PortAssigments;
//	BYTE _Flag0;
//	UINT16 _MAC_RX_Max_Hold_PPDU;
//	UINT16 _PRIME_MAC_Max_Conns;
//	UINT16 _MAC_Max_RX_Q_Length;
	BYTE _Reserved_2[7];
	BYTE _TMR_COH_Flags;
//	BYTE _SecurityProfile;

//	UINT16 _AddressType;
	BYTE _Reserved_3[3];
	BYTE _LongAddress[8];
//	UINT16 _PanId;
//	UINT16 _ShortAddress;
//	UINT16 _SegmentLength;
	BYTE _Reserved_4[6];
};

struct AttachRequest
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	UINT16 _PAN_Id;
	UINT16 _LBA_Address;  // short address..
};

struct AttachConfirm
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	UINT16 _Status;
	UINT16 _NetworkAddress; 
	UINT16 _PAN_Id;
};

struct AttachIndication
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	BYTE _IPv6_Address[16];
	BYTE _ExtendedAddress[8]; 
	BYTE _CapabilityInfo;
	BYTE _Reserved;
};

struct DetachRequest
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	BYTE _ExtendedAddress[8];
};

struct DetachConfirm
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	UINT16 _Status;
	BYTE _ExtendedAddress[8];
};

struct DetachIndication
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	BYTE _ExtendedAddress[8];
};

struct DiscoverNetworkRequest
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	BYTE _DiscoverType;
	BYTE _Duration;			
};

struct RouteDiscoverRequest
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	BYTE _DiscoverType;  // always 0x01 for route discover
	BYTE _MaxHops; // always 8 for now.
	UINT16 _ShortAddress;
};

struct PathDiscoverRequest
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	BYTE _DiscoverType;  // always 0x02 for route discover
	BYTE _Reserved;
	UINT16 _ShortAddress;
};

struct PathDiscoverConfirm
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	UINT16 _Status;
	UINT16 _ShortAddress;
	UINT16 _NumberOfDevices;      // max 8
	UINT16 _ShortAddressArray[8]; // max 8
};

//
// The PLC only sends the short address back so we can ignore teh extended address
//
struct PAN_Description
{
	BYTE _CoordAddressMode;
	BYTE _LQI;
	UINT16 _Coord_PAN_Address;
	UINT16 _ShortAddress;
//	BYTE _ExtendedAddress[8];
};
struct PAN_DescriptionVersion54
{
	BYTE _CoordAddressMode;
	BYTE _LQI;
	UINT16 _Coord_PAN_Address;
	UINT16 _ShortAddress;
//	BYTE _ExtendedAddress[8];
	BYTE _RoutingCost;
	BYTE _Reserved;
};

struct DiscoverNetworkConfirm
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	UINT16 _Status;
	UINT16 _PAN_Count;
//
// There can be more than one set of PAN Description
// We will just allocate extra memory and create an 
// array to access
//
	struct PAN_Description _PAN_Info[];
};

struct DiscoverNetworkConfirmVersion54
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	UINT16 _Status;
	UINT16 _PAN_Count;
//
// There can be more than one set of PAN Description
// We will just allocate extra memory and create an 
// array to access
//
	struct PAN_DescriptionVersion54 _PAN_Info[];
};

struct NetworkStartRequest
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	UINT16 _PAN_Id;
};

struct NetworkStartConfirm
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	UINT16 _Status;
};

struct SetInfo_TX
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	UINT16 _InfoType; // 0x0002
	UINT16 _InfoLength; // 16/18 depending on G3 version (5.0 and greater)
	BYTE _Flags;			// Band select, coh, tmr
	BYTE _Modulation;
	UINT16 _TX_Level;
	BYTE _ToneMask[14];
};

struct SetInfo_RX
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	UINT16 _InfoType; // 0x0003
	UINT16 _InfoLength; // 16/18 depending on G3 version (5.0 and greater)
	BYTE _Reserved;
	BYTE _Flags;				//Band select, coh, bli, agc
	UINT16 _GainValue;
	BYTE _ToneMask[14];
};

struct SetInfo_VendorProductId
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	UINT16 _InfoType; // 0x0004
	UINT16 _InfoLength; // 18
	UINT16 _VendorId;
	CHAR   _ProductId[16];
};

struct LoadSystemConfig
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;

	struct PortDesignation * _Port;
	struct SystemConfig * _SystemConfig;
	struct G3Configuration * _G3_Config;
};

struct PortDesignation
{
	UINT16 _Type;		// 0x0001
	UINT16 _Length; // 1
	BYTE _Port;
};

struct SystemConfig
{
	UINT16 _Type;		// 0x0003
	UINT16 _Length; // 26
	BYTE _Reserved_0[18 + 6];
	//UINT16 _SerialNumberLength;  // Not used by G3
	//BYTE _SerialNumber[16];
	//BYTE _EUI[6];
	BYTE _DeviceMode;
	BYTE _Reserved_1;
};

struct G3Configuration
{
	UINT16 _Type;		//0x0008
	UINT16 _Length;	//16
	BYTE _Reserved_0[2];
	BYTE _LongAddress[8];
	BYTE _Reserved_1[4];
	UINT16 _MAC_SegmentSize;  // obsolete for new dsp s/w but needs to be set to 239 for older versions.
};

struct Set_PSK_PIBs
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	UINT32 _Id;
	UINT16 _Index;
	UINT16 _Length;
	BYTE _Key[16];
};
struct Set_PIB_Replys
{
	struct Header _Header;
	struct CRC_Header _CRC_Header;
	UINT16 _Status;
};

//
//
//void * message is a pointer of the message struct
//int size is the size of the struct..
//
//
BYTE * MakeGenericMessage(void * message, int size);
int ReadGenericMessage(void * structure , int size, BYTE * message, int offset);
int ReadVariableLengthMessage(void ** msg, BYTE * message, int offset);
//
// This fills in the IPv6 aand UPD info it does not create the byte stream..
// The same function is used for the request and indication since the offset
// to the IPV6 info is the same in both messages..
//
void * FormDataTransferMessage(void * msg, BYTE * message, int offset);

void InitializeSystemConfigurationMessage(struct LoadSystemConfig * config);
void FreeSystemConfigMessage(struct LoadSystemConfig * config);
BYTE * MakeLoadSystemConfigurationMessage(struct LoadSystemConfig * config);
int ReadLoadSystemConfigurationMessage(struct LoadSystemConfig * configMessage, BYTE * message, int offset);

BYTE * MakeStatusMessage_1(struct StatusMessage * message, BYTE id, BYTE org, BYTE rpy, BYTE seq);

extern void MakeHeader(struct Header * header, int length);
extern void MakeCRC_Header(struct CRC_Header * crcHeader, void * header, int headerLength, void * body, int bodyLength);
extern void SetHeaderORG(BYTE org, struct Header * header);
extern void SetHeaderRPY(BYTE rpy, struct Header * header);
extern void SetHeaderSEQ(BYTE seq, struct Header * header);
extern BYTE GetHeaderORG(struct Header * header);
extern BYTE GetHeaderRPY(struct Header * header);
extern BYTE GetHeaderSEQ(struct Header * header);
