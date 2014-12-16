#pragma once
#include "UPlcConfigFile.h"

struct TLV
{
	UINT16 _Type;
	UINT16 _Length;
};


struct TLV_ExtendedAddress
{
	struct TLV _TLV;
	BYTE _ExtendedAddress[8];
};

struct TLV_IPv6_Address
{
	struct TLV _TLV;
	BYTE _IPv6_Address[16];
};


struct TLV_UINT16
{
	struct TLV _TLV;
	UINT16 _UINT16;
};

struct TLV_UINT32
{
	struct TLV _TLV;
	UINT32 _UINT32;
};

struct TLV_PATH
{
	struct TLV _TLV;
	UINT16 _Count;
	UINT16 _ShortAddress[8];
};

struct TLV_NodeInfo
{
	//
	// This header is here because the struct may repeat many times in the message..
	//
	struct TLV _TLV_Header;

	struct TLV_UINT16 _ShortAddress_TLV;
	struct TLV_ExtendedAddress _ExtendedAddress_TLV;
	struct TLV_PATH   _Path_TLV;

	struct TLV_UINT16 _TotalAttactes_TLV;
	struct TLV_UINT16 _TotalSuccessfullAttaches_TLV;

	struct TLV_UINT16 _TotalDetaches_TLV;
	struct TLV_UINT16 _TotalSuccessfullDetaches_TLV;

	struct TLV_UINT32 _PacketsSent_TLV;
	struct TLV_UINT32 _PacketsReceived_TLV;

	struct TLV_UINT32 _BytesSent_TLV;
	struct TLV_UINT32 _BytesReceived_TLV;
};

struct TLV_AttachRequest
{
	struct TLV _TLV_Header;
	struct TLV_UINT16 _PAN_Id_TLV;
	struct TLV_UINT16 _LBA_Address_TLV;
};


struct TLV_AttachConfirm
{
	struct TLV _TLV_Header;
	struct TLV_UINT16 _Status_TLV;
	struct TLV_UINT16 _NetworkAddress_TLV;
	struct TLV_UINT16 _PAN_Id_TLV;
};

struct TLV_AttachIndication
{
	struct TLV _TLV_Header;
	struct TLV_IPv6_Address _IPv6_Address_TLV;
	struct TLV_ExtendedAddress _ExtendedAddress_TLV;
	struct TLV_UINT16 _CapabilityInfo_TLV;
//	BYTE _Reserved; // keep it even..
};

#define _MAX_TLV_DESTINATIONS 10
struct TLV_EmeterTest
{
	struct TLV _TLV_Header;
	struct TLV_UINT16 _TLV_PayloadLength;
	struct TLV_UINT16 _TLV_MessagesPerTest;
	struct TLV_UINT16 _TLV_MessageRetries;
	struct TLV_UINT16 _TLV_MessageRetryDelay;
	struct TLV_UINT16 _TLV_MaxConsectutiveFails;
	struct TLV_UINT16 _TLV_InterCycleDelay;
	struct TLV_UINT16 _TLV_TestCycles;
	struct TLV_UINT16 _TLV_NumberOfExtendedDestinations;
	struct TLV_ExtendedAddress _TLV_ExtendedDestinations[_MAX_TLV_DESTINATIONS];
	struct TLV_UINT16 _TLV_NumberOfShortDestinations;
	struct TLV_UINT16 _TLV_ShortDestinations[_MAX_TLV_DESTINATIONS];
};

struct TLV_DetachRequest
{
	struct TLV _TLV_Header;
	struct TLV_ExtendedAddress _ExtendedAddress_TLV;
};

struct TLV_DetachConfirm
{
	struct TLV _TLV_Header;
	struct TLV_UINT16 _Status_TLV;
	struct TLV_ExtendedAddress _ExtendedAddress_TLV;
};

struct TLV_DetachIndication
{
	struct TLV _TLV_Header;
	struct TLV_ExtendedAddress _ExtendedAddress_TLV;
};

struct TLV_DataRequest
{
	struct TLV _TLV_Header;
	struct TLV_ExtendedAddress _ExtendedAddress_TLV;
	struct TLV_UINT16 _Data_TLV;
};

extern INT16 SwapOrder_Int16(INT16 data);
extern UINT16 SwapOrder_UInt16(UINT16 data);

extern UINT32 SwapOrder_Int32(INT32 data);
extern UINT32 SwapOrder_UInt32(UINT32 data);

extern BYTE * MakeGenericTLV(void * message);
extern int ReadGenericTLV(void * structure, BYTE * message, int offset);
extern BYTE * WrapTLV(struct TLV * tlv, BYTE * message);
extern UINT32 SwapInLine(BYTE * pointer, int size);
void Swap_TLV_WriteBytes(BYTE * msg, int len);
void Swap_TLV_ReadBytes(BYTE * msg, int len);
