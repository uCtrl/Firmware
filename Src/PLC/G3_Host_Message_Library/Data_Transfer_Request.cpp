#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Data_Transfer_Request.h"
#include "MessageIds.h"
#include "ByteArray.h"
#include "TLV_Messages.h"

BYTE Data_Transfer_Request::_NSDU = 0;

Data_Transfer_Request::Data_Transfer_Request(void)
{
	_pDTR = NULL;
	InitializeData();
}

Data_Transfer_Request::Data_Transfer_Request(BYTE * msg, int offset)
{
	_pDTR = NULL;
	ReadMessage(msg, offset);
}

Data_Transfer_Request::Data_Transfer_Request(Data_Transfer_Request & dtr)
{
	_pDTR = NULL;
	if (dtr._pDTR == NULL)
	{
		InitializeData();
	}
	else
	{
		int size = dtr.GetMsgSize();
		_pDTR = (DataTransferRequest *) malloc(size);
		memcpy(_pDTR, dtr._pDTR, size);
	}
}

Data_Transfer_Request::~Data_Transfer_Request(void)
{
	if (_pDTR != NULL)
	{
		free(_pDTR);
		_pDTR = NULL;
	}
}

int Data_Transfer_Request::GetMsgSize() 
{ 
	int size = 0;
	if (_pDTR == NULL)
	{
		InitializeData();
		size = sizeof(DataTransferRequest); // done in the header now.. - 2; /* remove the 2 xtra bytes in UDP struct */
	}
	else
	{
		size = _pDTR->_Header._Length + 4 /* header */;
	}
	return size; 
}

DataTransferRequest * Data_Transfer_Request::Get_DTR_Pointer()
{
	if (_pDTR == NULL)
	{
		InitializeData();
	}
	return _pDTR;
}

void Data_Transfer_Request::InitializeData()
{
	if (_pDTR != NULL)
	{
		delete _pDTR;
		_pDTR = NULL;
	}
	_pDTR = (DataTransferRequest *) malloc(sizeof(DataTransferRequest));
	memset(_pDTR, 0, sizeof(DataTransferRequest));

	_pDTR->_Header._Id = Data_Transfer_Id;
	_pDTR->_Header._Length = 4 /* CRC */ + sizeof(IPv6) + 8; /* min udp size */
	_pDTR->_Header._Origin = 0x80;
	_pDTR->_NSDU_Handle = _NSDU++;
	_pDTR->_UDP_Message._Length = 8;				/* min udp size */
	_pDTR->_IPv6_Header._PayloadLength = 8;	/* min udp size */
	_pDTR->_IPv6_Header._HopLimit = 8;
}

int Data_Transfer_Request::ReadMessage(BYTE * data, int offset)
{
	InitializeData();
	offset = ReadVariableLengthMessage((void **)&_pDTR, data, offset);
	//
	// Swap the UINT16 fields from Network order to Little Endian
	//
	SwapBytes();

	return offset;
}

HostMessage * Data_Transfer_Request::CreateMessage(BYTE * data, int offset)
{
	return new Data_Transfer_Request(data, offset);
}

TextString Data_Transfer_Request::ToString()
{
	TextString temp;
#ifdef P1901
	temp.Format("P1901 Data Transfer Request: Id=   %d\r\n", GetId());
#else
	temp.Format("G3 Data Transfer Request: Id=   %d\r\n", GetId());
#endif
	temp.AppendFormat("   NSDU_Handle:          %d\r\n", Get_NSDU());
	temp.AppendFormat("   QOS:                  %d\r\n", Get_QOS_Flag());
	temp.AppendFormat("   SEC:                  %d\r\n", Get_SEC_Flag());
	temp.AppendFormat("   Discovery Route:      %d\r\n", Get_DiscoveryRoute_Flag());
	
	ByteArray sa(16, Get_Source_Add());
	temp.AppendFormat("   Source Address:       0x%s\r\n", (char *)sa.ToString("%2.2X"));
	ByteArray da(16, Get_Destination_Add());
	temp.AppendFormat("   Destination Address:  0x%s\r\n", (char *)da.ToString("%2.2X"));
	temp.AppendFormat("   Hop Limit:            %d\r\n", Get_HopLimit());

	temp.AppendFormat("   Source Port:          0x%2.2X\r\n", Get_SourcePort());
	temp.AppendFormat("   Destination Port:     0x%2.2X\r\n", Get_DestinationPort());
	temp.AppendFormat("   Length:               %d\r\n", Get_UDP_Length());
	temp.AppendFormat("   CRC:                  0x%4.4X\r\n", Get_CRC());
	ByteArray data(Get_UDP_Length()-8, _pDTR->_UDP_Message._Data);
	temp.AppendFormat("   Data:\r\n%s\r\n\r\n", (char *)data.ToString());
	
	return temp;
}
void Data_Transfer_Request::SwapBytes()
{
	//
	// Swap the bytes... for the UINT16 fields.
	//
	_pDTR->_IPv6_Header._PayloadLength = SwapOrder_UInt16(_pDTR->_IPv6_Header._PayloadLength);
	_pDTR->_UDP_Message._DestinationPort = SwapOrder_UInt16(_pDTR->_UDP_Message._DestinationPort);
	_pDTR->_UDP_Message._SourcePort = SwapOrder_UInt16(_pDTR->_UDP_Message._SourcePort);
	_pDTR->_UDP_Message._Length = SwapOrder_UInt16(_pDTR->_UDP_Message._Length);
	_pDTR->_UDP_Message._CRC = SwapOrder_UInt16(_pDTR->_UDP_Message._CRC);
}
Message * Data_Transfer_Request::MakeMessage()
{
	SwapBytes();
	Message * msg = HostMessage::MakeMessage();
	//
	// Swap the bytes back
	//
	SwapBytes();

	return msg;
}
void Data_Transfer_Request::Set_Data(int length, BYTE * data)
{
	DataTransferRequest * temp = (DataTransferRequest* )FormDataTransferMessage(_pDTR, data, length);
	if (_pDTR != NULL)
	{
		free(_pDTR);
	}
	_pDTR = temp;
}

Message * Data_Transfer_Request::Get_Data()
{
	DataTransferRequest * dtr = Get_DTR_Pointer();

	Message * msg = new Message(dtr->_UDP_Message._Length-8, dtr->_UDP_Message._Data);
	return msg;
}

void Data_Transfer_Request::Set_NSDU(BYTE nsdu)
{
	Get_DTR_Pointer()->_NSDU_Handle = nsdu;
}
	
void Data_Transfer_Request::Set_QOS_Flag(BYTE qos)
{
	Get_DTR_Pointer()->_Flags &= 0x03;
	if (qos != 0)
	{
		Get_DTR_Pointer()->_Flags |= 0x04;
	}
}
void Data_Transfer_Request::Set_SEC_Flag(BYTE sec)
{
	Get_DTR_Pointer()->_Flags &= 0x05;
	if (sec != 0)
	{
		Get_DTR_Pointer()->_Flags |= 0x02;
	}
}
void Data_Transfer_Request::Set_DiscoveryRoute_Flag(BYTE dr)
{
	Get_DTR_Pointer()->_Flags &= 0x06;
	if (dr != 0)
	{
		Get_DTR_Pointer()->_Flags |= 0x01;
	}
}

void Data_Transfer_Request::Set_Destination_Add(BYTE * add)
{
	memcpy(Get_DTR_Pointer()->_IPv6_Header._DestinationAddress, add, 16);
}
void Data_Transfer_Request::Set_Source_Add(BYTE * add)
{
	memcpy(Get_DTR_Pointer()->_IPv6_Header._SourceAddress, add, 16);
}
void Data_Transfer_Request::Set_HopLimit(BYTE limit)
{
	Get_DTR_Pointer()->_IPv6_Header._HopLimit = limit;
}

void Data_Transfer_Request::Set_SourcePort(UINT16 port)
{
	Get_DTR_Pointer()->_UDP_Message._SourcePort = port;
}

void Data_Transfer_Request::Set_DestinationPort(UINT16 port)
{
	Get_DTR_Pointer()->_UDP_Message._DestinationPort = port;
}
	

BYTE Data_Transfer_Request::Get_NSDU()
{
	return Get_DTR_Pointer()->_NSDU_Handle;
}
	
BYTE Data_Transfer_Request:: Get_QOS_Flag()
{
	return (Get_DTR_Pointer()->_Flags & 0x04);
}

BYTE Data_Transfer_Request::Get_SEC_Flag()
{
	return (Get_DTR_Pointer()->_Flags & 0x02);
}

BYTE Data_Transfer_Request::Get_DiscoveryRoute_Flag()
{
	return (Get_DTR_Pointer()->_Flags & 0x01);
}

BYTE * Data_Transfer_Request::Get_Destination_Add()
{
	return Get_DTR_Pointer()->_IPv6_Header._DestinationAddress;
}
BYTE * Data_Transfer_Request::Get_Source_Add()
{
	return Get_DTR_Pointer()->_IPv6_Header._SourceAddress;
}

UINT8 Data_Transfer_Request::Get_HopLimit()
{
	return Get_DTR_Pointer()->_IPv6_Header._HopLimit;
}

UINT16 Data_Transfer_Request::Get_SourcePort()
{
	return Get_DTR_Pointer()->_UDP_Message._SourcePort;
}
UINT16 Data_Transfer_Request::Get_DestinationPort()
{
	return Get_DTR_Pointer()->_UDP_Message._DestinationPort;
}
UINT16 Data_Transfer_Request::Get_UDP_Length()
{
	return Get_DTR_Pointer()->_UDP_Message._Length;
}
UINT16 Data_Transfer_Request::Get_CRC()
{
	return Get_DTR_Pointer()->_UDP_Message._CRC;
}
void Data_Transfer_Request::CopyTo(HostMessage * msg)
{
	Data_Transfer_Request * copyToMsg = (Data_Transfer_Request *) msg;
	if (copyToMsg->_pDTR != NULL)
	{
		free(copyToMsg->_pDTR);
		copyToMsg->_pDTR = NULL;
	}
	if (_pDTR == NULL)
	{
		copyToMsg->InitializeData();
	}
	else
	{
		int size = GetMsgSize();
		copyToMsg->_pDTR = (DataTransferRequest *) malloc(size);
		memcpy(copyToMsg->_pDTR, _pDTR, size);
	}
}
