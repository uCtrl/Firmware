#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Data_Transfer_Indication.h"
#include "Data_Transfer_Confirm.h"
#include "MessageHeader.h"
#include "MessageIds.h"
#include "ByteArray.h"
#include "TLV_Messages.h"
#include "rtos.h"

Data_Transfer_Indication::Data_Transfer_Indication(void)
{
	_pDTI = NULL;
	InitializeData();
}

Data_Transfer_Indication::Data_Transfer_Indication(BYTE * msg, int offset)
{
	_pDTI = NULL;
	ReadMessage(msg, offset);
}

Data_Transfer_Indication::Data_Transfer_Indication(Data_Transfer_Indication & dti)
{
	_pDTI = NULL;
	if (dti._pDTI == NULL)
	{
		InitializeData();
	}
	else
	{
		int size = dti.GetMsgSize();
		_pDTI = (DataTransferIndication *) malloc(size);
		memcpy(_pDTI, dti._pDTI, size);
	}
}

Data_Transfer_Indication::~Data_Transfer_Indication(void)
{
	if (_pDTI != NULL)
	{
		free(_pDTI);
		_pDTI = NULL;
	}
}
extern Serial usbSerial;
#define USB_PRINTF_X(consttext, text, len) { \
                       usbSerial.printf(consttext); \
                       usbSerial.printf("0x"); \
                       for(int i = 0;i<len;i++){ \
                           usbSerial.printf("%x",text[i]); \
                       } \
                       usbSerial.printf("\r\n"); \
                   }
#define USB_PRINTF(consttext, text, len) { \
                       usbSerial.printf(consttext); \
                       usbSerial.printf("0x"); \
                       for(int i = 0;i<len;i++){ \
                           usbSerial.putc(text[i]); \
                       } \
                       usbSerial.printf("\r\n"); \
                   }

void printmem(DataTransferIndication* _pDTI)
{
	//header
	usbSerial.printf("         headerId: %d\r\n",_pDTI->_Header._Id);
	usbSerial.printf("     headerOrigin: %d\r\n",_pDTI->_Header._Origin);
	usbSerial.printf("     headerLength: %d\r\n\r\n",_pDTI->_Header._Origin);
	
	//crc header
	usbSerial.printf("         headerCRC: %d\r\n",_pDTI->_CRC_Header._HeaderCRC);
	usbSerial.printf("        messageCRC: %d\r\n\r\n",_pDTI->_CRC_Header._MessageCRC);
	
	//LQI
	usbSerial.printf("               LQI: %x\r\n",_pDTI->_LQI);
	
	//Flags
	usbSerial.printf("              FLAG: %x\r\n\r\n",_pDTI->_Flags);
	
	//IPv6
	    USB_PRINTF_X("        headerIPv6: ",_pDTI->_IPv6_Header._Header,4);
	usbSerial.printf(" payloadLengthIPv6: %d\r\n",_pDTI->_IPv6_Header._PayloadLength);
	usbSerial.printf("    nextHeaderIPv6: %d\r\n",_pDTI->_IPv6_Header._NextHeader);
	usbSerial.printf("         limitIPv6: %d\r\n",_pDTI->_IPv6_Header._HopLimit);
	    USB_PRINTF_X("        srcAdrIPv6: ",_pDTI->_IPv6_Header._SourceAddress,16);
	    USB_PRINTF_X("        desAdrIPv6: ",_pDTI->_IPv6_Header._DestinationAddress,16);
	
	//UDP
	usbSerial.printf("\r\n        udpSrcPort: %d\r\n",_pDTI->_UDP_Message._SourcePort);
	usbSerial.printf("       udpDestPort: %d\r\n",_pDTI->_UDP_Message._DestinationPort);
	usbSerial.printf("         udpLength: %d\r\n",_pDTI->_UDP_Message._Length);
	usbSerial.printf("            udpCRC: %d\r\n",_pDTI->_UDP_Message._CRC);
	      USB_PRINTF("           udpData: ",_pDTI->_UDP_Message._Data,_pDTI->_UDP_Message._Length-8);
}

int Data_Transfer_Indication::ReadMessage(BYTE * msg, int offset)
{
	InitializeData();
	offset = ReadVariableLengthMessage((void **)&_pDTI, msg, offset);
	//
	// Swap the network order fields to little endian
	//
	
	SwapBytes();
	
	printmem(_pDTI);
	return offset;
}

int Data_Transfer_Indication::GetMsgSize() 
{ 
	int size = 0;
	if (_pDTI == NULL)
	{
		InitializeData();
		size = sizeof(DataTransferIndication); // done in the header now.. - 2; /* 2 xtra bytes in struc*/
	}
	else
	{
		size = _pDTI->_Header._Length + 4;
	}
	return size; 
}

DataTransferIndication * Data_Transfer_Indication::Get_DTI_Pointer()
{
	if (_pDTI == NULL)
	{
		InitializeData();
	}
	return _pDTI;
}

void Data_Transfer_Indication::InitializeData()
{
	if (_pDTI != NULL)
	{
		delete _pDTI;
		_pDTI = NULL;
	}
	_pDTI = (DataTransferIndication *) malloc(sizeof(DataTransferIndication));
	memset(_pDTI, 0, sizeof(DataTransferIndication));

	_pDTI->_Header._Id = Data_Transfer_Id;
	_pDTI->_Header._Origin = 0x00;
	_pDTI->_Header._Length = 4 /* CRC */ + sizeof(IPv6) + 8; /* min udp size */

	_pDTI->_UDP_Message._Length = 8;				/* min udp size */
	_pDTI->_IPv6_Header._PayloadLength = 8;	/* min udp size */
	_pDTI->_IPv6_Header._HopLimit = 8;
}
void Data_Transfer_Indication::SwapBytes()
{
	_pDTI->_IPv6_Header._PayloadLength = SwapOrder_UInt16(_pDTI->_IPv6_Header._PayloadLength);
	_pDTI->_UDP_Message._DestinationPort = SwapOrder_UInt16(_pDTI->_UDP_Message._DestinationPort);
	_pDTI->_UDP_Message._SourcePort = SwapOrder_UInt16(_pDTI->_UDP_Message._SourcePort);
	_pDTI->_UDP_Message._Length = SwapOrder_UInt16(_pDTI->_UDP_Message._Length);
	_pDTI->_UDP_Message._CRC = SwapOrder_UInt16(_pDTI->_UDP_Message._CRC);
}

Message * Data_Transfer_Indication::MakeMessage()
{
	//
	// Swap the bytes... for the UINT16 fields.
	//
	SwapBytes();

	Message * msg = HostMessage::MakeMessage();
	//
	// Swap the bytes back
	//
	SwapBytes();

	return msg;
}

HostMessage * Data_Transfer_Indication::CreateMessage(BYTE * data, int offset)
{
	//
	// The origin and Id are the same for the confirm and indication messages.
	// We have to check the message length to decide which message we have.
	//
	HostMessage * message = NULL;
	MessageHeader header(data, offset);

	if (header.GetMessageLength() == 8)
	{
		message = new Data_Transfer_Confirm(data, offset);
	}
	else
	{
		message = new Data_Transfer_Indication(data, offset);
	}

	return message;
}

TextString Data_Transfer_Indication::ToString()
{
	TextString temp;
#ifdef P1901
	temp.Format("P1901.2 Data Transfer Indication: Id=   %d\r\n", GetId());
#else
	temp.Format("G3 Data Transfer Indication: Id=   %d\r\n", GetId());
#endif
	temp.AppendFormat("   Link Quality Indicator:   %d\r\n", Get_LQI());
	temp.AppendFormat("   Confirm Flag:             %d\r\n", Get_Confirmation_Flag());
	temp.AppendFormat("   Security Flag:            %d\r\n", Get_SEC_Flag());

	ByteArray sa(16, Get_Source_Add());
	temp.AppendFormat("   Source Address:       0x%s\r\n", (char *)sa.ToString("%2.2X"));
	ByteArray da(16, Get_Destination_Add());
	temp.AppendFormat("   Destination Address:  0x%s\r\n", (char *)da.ToString("%2.2X"));
	temp.AppendFormat("   Hop Limit:            %d\r\n", Get_HopLimit());

	temp.AppendFormat("   Source Port:          0x%2.2X\r\n", Get_SourcePort());
	temp.AppendFormat("   Destination Port:     0x%2.2X\r\n", Get_DestinationPort());
	temp.AppendFormat("   Length:               %d\r\n", Get_UDP_Length());
	temp.AppendFormat("   CRC:                  0x%4.4X\r\n", Get_CRC());

	ByteArray data(Get_UDP_Length()-8, _pDTI->_UDP_Message._Data);
	temp.AppendFormat("   Data:%.*s",30,_pDTI->_UDP_Message._Data);
	/*
	temp.AppendFormat("   Data:                 \r\n%s\r\n\r\n", (char *)data.ToString());*/

	return temp;
}
Message * Data_Transfer_Indication::Get_Data()
{
	DataTransferIndication * dti = Get_DTI_Pointer();
	Message * msg = new Message(dti->_UDP_Message._Length-8, dti->_UDP_Message._Data);
	return msg;
}

BYTE Data_Transfer_Indication::Get_LQI()
{
	return Get_DTI_Pointer()->_LQI;
}
BYTE Data_Transfer_Indication::Get_Confirmation_Flag()
{
	return (Get_DTI_Pointer()->_Flags & 0x80);
}
BYTE Data_Transfer_Indication::Get_SEC_Flag()
{
	return (Get_DTI_Pointer()->_Flags & 0x01);
}

BYTE * Data_Transfer_Indication::Get_Destination_Add()
{
	return Get_DTI_Pointer()->_IPv6_Header._DestinationAddress;
}

BYTE * Data_Transfer_Indication::Get_Source_Add()
{
	return Get_DTI_Pointer()->_IPv6_Header._SourceAddress;
}

UINT8 Data_Transfer_Indication::Get_HopLimit()
{
	return Get_DTI_Pointer()->_IPv6_Header._HopLimit;
}

UINT16 Data_Transfer_Indication::Get_SourcePort()
{
	return Get_DTI_Pointer()->_UDP_Message._SourcePort;
}

UINT16 Data_Transfer_Indication::Get_DestinationPort()
{
	return Get_DTI_Pointer()->_UDP_Message._DestinationPort;
}

UINT16 Data_Transfer_Indication::Get_UDP_Length()
{
	return Get_DTI_Pointer()->_UDP_Message._Length;
}
UINT16 Data_Transfer_Indication::Get_CRC()
{
	return Get_DTI_Pointer()->_UDP_Message._CRC;
}
void Data_Transfer_Indication::CopyTo(HostMessage * msg)
{
	Data_Transfer_Indication * copyToMsg = (Data_Transfer_Indication *) msg;
	if (copyToMsg->_pDTI != NULL)
	{
		free(copyToMsg->_pDTI);
		copyToMsg->_pDTI = NULL;
	}
	if (_pDTI == NULL)
	{
		copyToMsg->InitializeData();
	}
	else
	{
		int size = GetMsgSize();
		copyToMsg->_pDTI = (DataTransferIndication *) malloc(size);
		memcpy(copyToMsg->_pDTI, _pDTI, size);
	}
}
