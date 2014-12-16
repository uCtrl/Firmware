#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Discover.h"
#include "RouteRequest.h"
#include "PathRequest.h"
#include "PathConfirm.h"
#include "Get_System_Info.h"
#include "Status_Message.h"
#include "MessageIds.h"
#include "ByteArray.h"

int LastDiscoverType = 0;

Discover_Network_Request::Discover_Network_Request(void)
{
	InitializeData();
}

Discover_Network_Request::Discover_Network_Request(BYTE * msg, int offset)
{
	ReadGenericMessage(&_DiscoverNetworkRequest, sizeof(_DiscoverNetworkRequest), msg, offset);
}

Discover_Network_Request::Discover_Network_Request(const Discover_Network_Request & msg)
{
	memcpy(&_DiscoverNetworkRequest, & msg._DiscoverNetworkRequest, sizeof(DiscoverNetworkRequest));
}

Discover_Network_Request::~Discover_Network_Request(void)
{
}

void Discover_Network_Request::InitializeData()
{
	memset(&_DiscoverNetworkRequest, 0, sizeof(_DiscoverNetworkRequest));
	_DiscoverNetworkRequest._Header._Id = Discover_Id;
	_DiscoverNetworkRequest._Header._Origin = 0x80;
	_DiscoverNetworkRequest._Duration = 1;
	_DiscoverNetworkRequest._DiscoverType = NetworkDiscover;
	LastDiscoverType = NetworkDiscover;
};

HostMessage * Discover_Network_Request::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = NULL;

	Discover_Network_Request nr(data,offset);
	if (nr.GetDiscoverType() == NetworkDiscover)
	{
		msg = new Discover_Network_Request(data, offset);
	}
	else if (nr.GetDiscoverType() == RouteDiscover)
	{
		msg = new RouteRequest(data, offset);
	}
	else if (nr.GetDiscoverType() == PathDiscover)
	{
		msg = new PathRequest(data, offset);
	}
	return msg;
}

TextString Discover_Network_Request::ToString()
{
	TextString temp;
	temp.Format("Discover_Request: Id=   %d\r\n", GetId());
	temp.AppendFormat("   Discover_Request Type: %d\r\n", _DiscoverNetworkRequest._DiscoverType);
	temp.AppendFormat("   Duration:      %d\r\n\r\n", _DiscoverNetworkRequest._Duration);
	return temp;
}

/*

Discover Confirm

*/
Discover_Network_Confirm::Discover_Network_Confirm(void)
{
	_pDiscoverNetworkConfirm = NULL;
	_pDiscoverNetworkConfirmVersion54 = NULL;
	InitializeData();
}

Discover_Network_Confirm::Discover_Network_Confirm(BYTE * msg, int offset) 
{
	_pDiscoverNetworkConfirm = NULL;
	_pDiscoverNetworkConfirmVersion54 = NULL;

	ReadVariableLengthMessage((void**)&_pDiscoverNetworkConfirmVersion54, msg, offset);
}

Discover_Network_Confirm::Discover_Network_Confirm( Discover_Network_Confirm & msg)
{
	_pDiscoverNetworkConfirm = NULL;
	_pDiscoverNetworkConfirmVersion54 = NULL;

	if (msg._pDiscoverNetworkConfirm != NULL)
	{
		_pDiscoverNetworkConfirm = (DiscoverNetworkConfirm *)malloc(msg.GetMsgSize());
		memcpy(_pDiscoverNetworkConfirm, msg._pDiscoverNetworkConfirm, msg.GetMsgSize());
	}
	else if (msg._pDiscoverNetworkConfirmVersion54 != NULL)
	{
		_pDiscoverNetworkConfirmVersion54 = (DiscoverNetworkConfirmVersion54 *)malloc(msg.GetMsgSize());
		memcpy(_pDiscoverNetworkConfirmVersion54, msg._pDiscoverNetworkConfirmVersion54, msg.GetMsgSize());
	}
	else
	{
		InitializeData();
	}

}
void * Discover_Network_Confirm::GetHeader()
{ 
	void * header = _pDiscoverNetworkConfirm; 
	header = _pDiscoverNetworkConfirmVersion54;
	return header;
}

Discover_Network_Confirm::~Discover_Network_Confirm(void)
{
	if (_pDiscoverNetworkConfirm != NULL)
	{
		free(_pDiscoverNetworkConfirm);
		_pDiscoverNetworkConfirm = NULL;
	}

	if (_pDiscoverNetworkConfirmVersion54 != NULL)
	{
		free(_pDiscoverNetworkConfirmVersion54);
		_pDiscoverNetworkConfirmVersion54 = NULL;
	}
}

int Discover_Network_Confirm::GetMsgSize() 
{ 
	int size = 0;
	
	if (_pDiscoverNetworkConfirm != NULL)
	{
		Header *pHeader = (Header *)_pDiscoverNetworkConfirm;
		size = pHeader->_Length + 4;
	}
	else if (_pDiscoverNetworkConfirmVersion54 != NULL)
	{
		Header *pHeader = (Header *)_pDiscoverNetworkConfirmVersion54;
		size = pHeader->_Length + 4;
	}
	else 
	{
		size = sizeof(Header) + sizeof(CRC_Header) + 4;
	}
	return size; 
}
void Discover_Network_Confirm::InitializeData()
{
	_pDiscoverNetworkConfirm = NULL;
	_pDiscoverNetworkConfirmVersion54 = NULL;

	_pDiscoverNetworkConfirmVersion54 = (DiscoverNetworkConfirmVersion54 *) malloc(sizeof(DiscoverNetworkConfirmVersion54));
	memset(_pDiscoverNetworkConfirmVersion54, 0, sizeof(DiscoverNetworkConfirmVersion54));
	_pDiscoverNetworkConfirmVersion54->_Header._Id = Discover_Id;
	_pDiscoverNetworkConfirmVersion54->_Header._Origin = 0;
}

HostMessage * Discover_Network_Confirm::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = NULL;

	if (LastDiscoverType == RouteDiscover)
	{
		msg = new Status_Message(data, offset);
	}
	else if (LastDiscoverType == PathDiscover)
	{
		msg = new PathConfirm(data, offset);
	}
	else if (LastDiscoverType == NetworkDiscover)
	{
		msg = new Discover_Network_Confirm(data, offset);
	}
	return msg;
}

TextString Discover_Network_Confirm::ToString()
{
	TextString temp;
	temp.Format("Discover_Confirm: Id=   %d\r\n", GetId());
	temp.AppendFormat("   Status:              0x%4.4X\r\n", (int)_pDiscoverNetworkConfirmVersion54->_Status);
	temp.AppendFormat("   PAN Count:           %d\r\n", (int)_pDiscoverNetworkConfirmVersion54->_PAN_Count);
	int  panCount = _pDiscoverNetworkConfirmVersion54->_PAN_Count;
	for(int index = 0; index < panCount; index++)
	{
		PAN_DescriptionVersion54 * currentPan = & _pDiscoverNetworkConfirmVersion54->_PAN_Info[index];
		temp.AppendFormat("   PAN Id:              0x%2.2X\r\n", currentPan->_Coord_PAN_Address);
		temp.AppendFormat("   PAN Address:         0x%2.2X\r\n", currentPan->_ShortAddress);
		temp.AppendFormat("   Coord Address Mode:  %d\r\n", currentPan->_CoordAddressMode);
		//temp.AppendFormat("   LQI:                 %d\r\n", currentPan->_LQI);
		temp.AppendFormat("   Route Cost:          %d\r\n", currentPan->_RoutingCost);
	}

	temp.Append("\r\n");
	return temp;
}

UINT16 Discover_Network_Confirm::GetStatus()
{
	UINT16 status = 0xFFFF;

	if (_pDiscoverNetworkConfirm != NULL)
	{
		status = _pDiscoverNetworkConfirm->_Status;
	}
	else if (_pDiscoverNetworkConfirmVersion54 != NULL)
	{
		status = _pDiscoverNetworkConfirmVersion54->_Status;
	}
	return status;
}

UINT16 Discover_Network_Confirm::Get_PAN_Count()
{
	UINT16 count = 0;
	if (_pDiscoverNetworkConfirm != NULL)
	{
		count = _pDiscoverNetworkConfirm->_PAN_Count;
	}
	else if (_pDiscoverNetworkConfirmVersion54 != NULL)
	{
		count = _pDiscoverNetworkConfirmVersion54->_PAN_Count;
	}
	return count;
}

PAN_Description * Discover_Network_Confirm::Get_PAN(int index)
{
	PAN_Description * pan = NULL;
	if (_pDiscoverNetworkConfirm != NULL  && index < _pDiscoverNetworkConfirm->_PAN_Count)
	{
		pan = & _pDiscoverNetworkConfirm->_PAN_Info[index];
	}
	return pan;
}
PAN_DescriptionVersion54 * Discover_Network_Confirm::Get_PAN_Version54(int index)
{
	PAN_DescriptionVersion54 * pan = NULL;
	if (_pDiscoverNetworkConfirmVersion54 != NULL  && index < _pDiscoverNetworkConfirmVersion54->_PAN_Count)
	{
		pan = & _pDiscoverNetworkConfirmVersion54->_PAN_Info[index];
	}
	return pan;
}
void Discover_Network_Confirm::CopyTo(HostMessage * msg)
{
	Discover_Network_Confirm * copyToMsg = (Discover_Network_Confirm *) msg;
	if (copyToMsg->_pDiscoverNetworkConfirm != NULL)
	{
		free(copyToMsg->_pDiscoverNetworkConfirm);
		copyToMsg->_pDiscoverNetworkConfirm = NULL;
	}
	if (copyToMsg->_pDiscoverNetworkConfirmVersion54 != NULL)
	{
		free(copyToMsg->_pDiscoverNetworkConfirmVersion54);
		copyToMsg->_pDiscoverNetworkConfirmVersion54 = NULL;
	}

	if (_pDiscoverNetworkConfirm != NULL)
	{
		int size = GetMsgSize();
		copyToMsg->_pDiscoverNetworkConfirm = (DiscoverNetworkConfirm *) malloc(size);
		memcpy(copyToMsg->_pDiscoverNetworkConfirm, _pDiscoverNetworkConfirm, size);
	}
	else if (_pDiscoverNetworkConfirmVersion54 != NULL)
	{
		int size = GetMsgSize();
		copyToMsg->_pDiscoverNetworkConfirmVersion54 = (DiscoverNetworkConfirmVersion54 *) malloc(size);
		memcpy(copyToMsg->_pDiscoverNetworkConfirmVersion54, _pDiscoverNetworkConfirmVersion54, size);
	}
	else
	{
		copyToMsg->InitializeData();
	}
}
