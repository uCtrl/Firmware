#include <iostream>
#include <fstream>

#include "UPlcConfigFile.h"
#include "ServiceNode.h"
#include "CriticalSection.h"
#include "ByteArray.h"
#include "TLV_Messages.h"

using namespace std;

ServiceNode::ServiceNode(void)
{
	memset(_ExtendedAddress, 0, sizeof(_ExtendedAddress));
	memset(_IPv6_Address, 0, sizeof(_IPv6_Address));
	memset(_Path, 0, sizeof(_Path));

	_ShortAddress = 0;
	_PAN_Id = 0;
	_PathCount = 0;

	_Connected = FALSE;
	_TotalConnects = 0;
	_TotalDisconnects = 0;

	_TotalSuccessfullConnects= 0;
	_TotalSuccessfullDisconnects= 0;

	_PacketsReceived = 0;
	_PacketsSent = 0;
	_BytesReceived = 0;
	_BytesSent = 0;

	_TotalMessageRetries = 0;
	_TotalMessageRoundTripTime = 0;
	_ConsectutiveFailures = 0;
}

ServiceNode::ServiceNode(ServiceNode & serviceNode)
{
	_Connected = serviceNode._Connected;
	memcpy(_ExtendedAddress, serviceNode._ExtendedAddress, sizeof(_ExtendedAddress));
	memcpy(_IPv6_Address, serviceNode._IPv6_Address, sizeof(_IPv6_Address));
	memcpy(_Path, serviceNode._Path, sizeof(_Path));

	_PathCount = serviceNode._PathCount;

	_ShortAddress = serviceNode._ShortAddress;
	_PAN_Id = 0;

	_TotalConnects = serviceNode._TotalConnects;;
	_TotalDisconnects = serviceNode._TotalDisconnects;

	_TotalSuccessfullConnects = serviceNode._TotalSuccessfullConnects;
	_TotalSuccessfullDisconnects = serviceNode._TotalSuccessfullDisconnects;

	_PacketsReceived = serviceNode._PacketsReceived;
	_PacketsSent = serviceNode._PacketsSent;
	_BytesReceived = serviceNode._BytesReceived;
	_BytesSent = serviceNode._BytesSent;

	_TotalMessageRetries = serviceNode._TotalMessageRetries;
	_TotalMessageRoundTripTime = serviceNode._TotalMessageRoundTripTime;
	_ConsectutiveFailures = serviceNode._ConsectutiveFailures;

}

ServiceNode::ServiceNode(BYTE * extendedAddress, BYTE * ipv6Address)
{
	memcpy(_ExtendedAddress, extendedAddress, sizeof(_ExtendedAddress));
	memset(_Path, 0, sizeof(_Path));

	Set_IPv6_Address(ipv6Address);

	_Connected = TRUE;
	_PAN_Id = 0;
	_PathCount = 0;

	_TotalConnects = 0;
	_TotalDisconnects = 0;
	_TotalSuccessfullConnects = 0;
	_TotalSuccessfullDisconnects = 0;

	_PacketsReceived = 0;
	_PacketsSent = 0;
	_BytesReceived = 0;
	_BytesSent = 0;

	_TotalMessageRetries = 0;
	_TotalMessageRoundTripTime = 0;
	_ConsectutiveFailures = 0;
}


ServiceNode::~ServiceNode(void)
{
}

void ServiceNode::Set_IPv6_Address(BYTE * ipv6Address)
{
	memcpy(_IPv6_Address, ipv6Address, sizeof(_IPv6_Address));
	memcpy(&_ShortAddress, &_IPv6_Address[14], sizeof(UINT16));
	_ShortAddress = SwapOrder_UInt16(_ShortAddress);
}

void ServiceNode::ResetStats()
{

	_TotalConnects = 0;
	_TotalDisconnects = 0;
	_TotalSuccessfullConnects = 0;
	_TotalSuccessfullDisconnects = 0;
	_PacketsReceived = 0;
	_PacketsSent = 0;
	_BytesReceived = 0;
	_BytesSent = 0;
	_TotalMessageRetries = 0;
	_TotalMessageRoundTripTime = 0;
	_ConsectutiveFailures = 0;
}
void ServiceNodeList::DeleteData(void * data)
{
	ServiceNode * node = (ServiceNode *) data;
	delete node;
}


bool ServiceNodeList::Compare(void * node, void * extendedAddress)
{
	ServiceNode * sn = (ServiceNode *) node;
	BYTE * ea = (BYTE*)extendedAddress;
	return (memcmp(sn->_ExtendedAddress, ea, 8) == 0);
}

void ServiceNodeList::Disconnect(ServiceNode * serviceNode)
{
	_CriticalSection.Lock();

	ServiceNode * sn = (ServiceNode *) Find(serviceNode->_ExtendedAddress);
	if (sn != NULL)
	{
		//
		// Update the connection stats
		//
		if (sn->_Connected == TRUE)
		{
			sn->_TotalDisconnects++;
		}
		sn->_Connected = FALSE;
		//
		// Copy the connect stats back to the service node
		//
		serviceNode->_TotalConnects = sn->_TotalConnects;
		serviceNode->_Connected = sn->_Connected;
		serviceNode->_TotalDisconnects = sn->_TotalDisconnects;
	}
	_CriticalSection.UnLock();
}

BOOL ServiceNodeList::IsConnected(ServiceNode * serviceNode)
{
	_CriticalSection.Lock();
	BOOL connected = FALSE;
	ServiceNode * sn = (ServiceNode *) Find(serviceNode->_ExtendedAddress);
	if (sn != NULL)
	{
			connected = sn->_Connected;
			serviceNode->_Connected = connected;
	}
	_CriticalSection.UnLock();
	return connected;
}

void ServiceNodeList::Disconnect(BYTE * extendedAddress)
{
	ServiceNode * sn = (ServiceNode *) Find(extendedAddress);
	if (sn != NULL)
	{
		//
		// Update the connection stats
		//
		sn->_TotalDisconnects++;

		memset(sn->_Path, 0, 16);
		sn->_PathCount = 0;
	}
	_CriticalSection.UnLock();
}

BOOL ServiceNodeList::IsConnected(BYTE * extendedAddress)
{
	BOOL connected = FALSE;

	_CriticalSection.Lock();
	ServiceNode * sn = (ServiceNode *) Find(extendedAddress);
	if (sn != NULL)
	{
			connected = sn->_Connected;
	}
	_CriticalSection.UnLock();
	return connected;
}

ServiceNode * ServiceNodeList::GetServiceNode(BYTE * extendedAddress)
{
	return (ServiceNode *) Find(extendedAddress);
}

ServiceNode * ServiceNodeList::GetServiceNode(UINT16 shortAddress)
{
	Node  * node = GetHead();
	ServiceNode * sn = NULL;
	while (node != NULL)
	{
		ServiceNode * temp = (ServiceNode *)node->GetData();
		if (temp->_ShortAddress == shortAddress)
		{
			sn = temp;
			break;
		}
		node = node->GetNext();
	}
	return sn;
}
void ServiceNodeList::ResetStats()
{
	Node  * node = GetHead();
	while (node != NULL)
	{
		ServiceNode * sn = (ServiceNode *)node->GetData();
		sn->ResetStats();
		node = node->GetNext();
	}
}
