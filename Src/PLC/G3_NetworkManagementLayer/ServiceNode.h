#pragma once
#include "CriticalSection.h"
#include "LinkedList.h"

class ServiceNodeList;

class ServiceNode
{
public:
	BYTE _ExtendedAddress[8];
	BYTE _IPv6_Address[16];
	UINT16 _ShortAddress;
	UINT16 _PAN_Id;

	BOOL _Connected;

	UINT16 _PathCount;
	UINT16 _Path[8];

	UINT16 _TotalConnects;
	UINT16 _TotalDisconnects;
	UINT16 _TotalSuccessfullConnects;
	UINT16 _TotalSuccessfullDisconnects;

	UINT32 _PacketsReceived;
	UINT32 _PacketsSent;
	UINT32 _BytesReceived;
	UINT32 _BytesSent;

	UINT32 _TotalMessageRetries;
	UINT32 _TotalMessageRoundTripTime;
	UINT32 _ConsectutiveFailures;

	ServiceNode();
	ServiceNode(BYTE * extendedAddress, BYTE * ipv6Address);
	ServiceNode(ServiceNode & serviceNode);

	~ServiceNode();

	void Set_IPv6_Address(BYTE * ipv6Address);
	void ResetStats();
};

class ServiceNodeList : public LinkedList
{
protected:
//	CriticalSection _CriticalSection;
	virtual void DeleteData(void * data);
	virtual bool Compare(void * data0, void * data1);
public:
	ServiceNodeList(){};
	virtual ~ServiceNodeList() { RemoveAll(); }

	void Disconnect(ServiceNode * sn);
	BOOL IsConnected(ServiceNode * sn);

	void Disconnect(BYTE * extendedAddress);
	BOOL IsConnected(BYTE * extendedAddress);

	ServiceNode * GetServiceNode(BYTE * extendedAddress);
	ServiceNode * GetServiceNode(UINT16 shortAddress);

	void ResetStats();
};
