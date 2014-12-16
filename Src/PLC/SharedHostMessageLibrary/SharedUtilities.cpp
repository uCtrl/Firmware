#include "HostMessages.h"
#include "TLV_Messages.h"
#include "UPlcConfigFile.h"

void MakeCRC_Header(struct CRC_Header * crcHeader, void * header, int headerLength, void * body, int bodyLength)
{
	crcHeader->_HeaderCRC = CRC16_BlockChecksum( header, headerLength);
	if (bodyLength == 0)
	{
		crcHeader->_MessageCRC = 0;
	}
	else
	{
		crcHeader->_MessageCRC = CRC16_BlockChecksum(body, bodyLength);
	}
}
void SetHeaderORG(BYTE org, struct Header * header) { if (org != 0) header->_Origin |= 0x80; else (header->_Origin & 0x7F);}
void SetHeaderRPY(BYTE rpy, struct Header * header) { if (rpy != 0) header->_Origin |= 0x40; else (header->_Origin & 0xBF);} 
void SetHeaderSEQ(BYTE seq, struct Header * header) { if (seq != 0) header->_Origin |= (seq & 0x0F); else (header->_Origin & 0xF0);} 
BYTE GetHeaderORG(struct Header * header) { return (header->_Origin & 0x80); }
BYTE GetHeaderRPY(struct Header * header) { return (header->_Origin & 0x40); }
BYTE GetHeaderSEQ(struct Header * header) { return (header->_Origin & 0x0F); }
//
//
//void * message is a pointer of the message struct
//int size is the size of the struct..
//
//
BYTE * MakeGenericMessage(void * message, int size)
{
	int payloadLength = size - sizeof(struct Header);
	int headerLength = sizeof(struct Header) + sizeof(struct CRC_Header); 
	struct Header * header = (struct Header *)message;
	BYTE * pMessage = (BYTE *)message;
	BYTE * msg = (BYTE *) malloc(size);
	struct CRC_Header * crcHeader = (struct CRC_Header *)(&pMessage[sizeof(struct Header)]);

	header->_Length = (UINT16) payloadLength;

	MakeCRC_Header(crcHeader, header, sizeof(struct Header), & pMessage[headerLength], size-headerLength);

	memcpy(msg, message, size);
	return msg;
}

int ReadGenericMessage(void * structure , int size, BYTE * message, int offset)
{
	//
	// This code is here to handle the change to a message length
	// for different versions of the PLC.
	//
	// Must not copy data to the message structure that is not sent by the plc
	// and must not copy past the end of the structure.
	//
	struct Header * header = (struct Header *)message;
	int length = header->_Length + 4;

	int bytesToCopy = size;
	if (length < size)
	{
		bytesToCopy = length;
	}
	memset(structure, 0, size);

	memcpy(structure, & message[offset], bytesToCopy);
	offset += bytesToCopy;
	return offset;
}

extern Serial usbSerial;

int ReadVariableLengthMessage(void ** msg, BYTE * message, int offset)
{
	struct Header * header = (struct Header *)message;
	int length = header->_Length + 4;
	if (*msg != NULL)
	{
		free(*msg);
	}
	*msg = malloc(length);
	memcpy(*msg, &message[offset], length);
	offset += length;
	return offset;
}

BYTE * MakeGenericTLV(void * message)
{
	//
	// Make the header..
	//
	BYTE temp;
	BYTE * msg;
	UINT16 size;
	UINT16 type;
	BYTE * bytePointer;
	int headerSize;
	struct TLV * tlv;

	tlv = (struct TLV*)message;
	headerSize = sizeof(struct TLV);

	bytePointer =  (BYTE *)message;
	type  = SwapOrder_UInt16(tlv->_Type);
	size  = SwapOrder_UInt16(tlv->_Length);
	msg = (BYTE *)malloc(tlv->_Length + headerSize);

	memcpy(msg, &type, 2);
	memcpy(&msg[2], &size, 2);
	memcpy(&msg[headerSize], & bytePointer[headerSize], tlv->_Length);

	if (tlv->_Length == 2)
	{
		temp = msg[headerSize];
		msg[headerSize] = msg[headerSize+1];
		msg[headerSize+1] = temp;
	}
	else if (tlv->_Length == 4)
	{
		temp = msg[headerSize];
		msg[headerSize] = msg[headerSize+3];
		msg[headerSize+3] = temp;

		temp = msg[headerSize+1];
		msg[headerSize+1]= msg[headerSize+2];
		msg[headerSize+2] = temp;
	}

	return msg;
}

int ReadGenericTLV(void * structure, BYTE * message, int offset)
{
	BYTE * msg = (BYTE *)structure;
	int headerSize = sizeof(struct TLV);
	BYTE temp;
	UINT16 type;
	UINT16 size;
	//
	// Read the header to get the length
	//
	struct TLV  * tlv = (struct TLV *) & message[offset];
	type = SwapOrder_UInt16(tlv->_Type);
	size = SwapOrder_UInt16(tlv->_Length);

	memcpy( msg, &type, sizeof(UINT16));
	memcpy(&msg[2], & size, sizeof(UINT16));

	memcpy(&msg[4], & message[offset+4], size);

	
	if (size == 2)
	{
		temp = msg[headerSize];
		msg[headerSize] = msg[headerSize+1];
		msg[headerSize+1] = temp;
	}
	else if (size == 4)
	{
		temp = msg[headerSize];
		msg[headerSize] = msg[headerSize+3];
		msg[headerSize+3] = temp;

		temp = msg[headerSize+1];
		msg[headerSize+1]= msg[headerSize+2];
		msg[headerSize+2] = temp;
	}

	offset += size + 4;
	return offset;
}

BYTE * WrapTLV(struct TLV * tlv, BYTE * message)
{
	//
	// Make the header..
	//
	BYTE * msg;
	UINT16 size;
	UINT16 type;
	BYTE * bytePointer;
	int headerSize;

	struct TLV * _tlv;

	_tlv = (struct TLV*)message;
	headerSize = sizeof(struct TLV);

	bytePointer =  (BYTE *)message;
	type  = SwapOrder_UInt16(tlv->_Type);
	size  = SwapOrder_UInt16(tlv->_Length);
	msg = (BYTE *)malloc(tlv->_Length + headerSize);

	memcpy(msg, &type, 2);
	memcpy(&msg[2], &size, 2);
	memcpy(&msg[headerSize], & bytePointer[headerSize], tlv->_Length);

	return msg;
}

void Swap_TLV_WriteBytes(BYTE * msg, int len)
{
	//
	// First two bytes is the TLV type
	//
	UINT32 type = 0;
	UINT32 length = 0;
	int offset = 0;

	while (offset < len)
	{
		memcpy(&type, &msg[offset], 2);
		SwapInLine(&msg[offset], 2);

		offset += 2;
		//
		// Next two bytes is the tlv length
		//
		memcpy(&length, &msg[offset], 2);
		SwapInLine(&msg[offset], 2);
		offset += 2;

		if (length == 2 || length == 4)
		{
			SwapInLine(&msg[offset], length);
		}
		if (type >= 0x700 && type <=0x0FFF)
		{
			offset += length;
		}
	}
}
void Swap_TLV_ReadBytes(BYTE * msg, int len)
{
	//
	// First two bytes is the TLV type
	//
	UINT32 type = 0;
	UINT32 length = 0;
	int offset = 0;

	while (offset < len)
	{
		SwapInLine(&msg[offset], 2);
		memcpy(&type, &msg[offset], 2);

		offset += 2;
		//
		// Next two bytes is the tlv length
		//
		SwapInLine(&msg[offset], 2);
		memcpy(&length, &msg[offset], 2);
		offset += 2;

		if (length == 2 || length == 4)
		{
			SwapInLine(&msg[offset], length);
		}
		if (type >= 0x700 && type <=0x0FFF)
		{
			offset += length;
		}
	}
}
