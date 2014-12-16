#include "HostMessages.h"

#define IPV6_PSEUDO_HEADER_LEN 46

unsigned short GenerateCRC16Udp(DataTransfer * const dt)//IPv6_Header,ipv6dst,udplen,zero,nextheader,udp)
{
	char *data = new char[IPV6_PSEUDO_HEADER_LEN]();
	memcpy(data, dt->_IPv6_Header._SourceAddress, 16);
	memcpy(data+16, dt->_IPv6_Header._DestinationAddress, 16);
	memcpy(data+32+2, &(dt->_UDP_Message._Length), 2); //udp length is only 2 byte long
	memcpy(data+36+3, &(dt->_IPv6_Header._NextHeader), 1);
	
	memcpy(data+40, &(dt->_UDP_Message._SourcePort), 2);
	memcpy(data+42, &(dt->_UDP_Message._DestinationPort), 2);
	//memcpy(data+44, &(dt->_UDP_Message._Length), 2);
	
	unsigned short retvalue = CRC16_BlockChecksum(data, IPV6_PSEUDO_HEADER_LEN);
	delete [] data;
	return retvalue;
}

//
// This fills in the IPv6 aand UPD info it does not create the byte stream..
// The same function is used for the request and indication since the offset
// to the IPV6 info is the same in both messages..
//
// The assumption is that the IPv6 and port addresses are filled out or will
// be filled out after the IPv6 messages is formed with the data..
//
//
void * FormDataTransferMessage(void * transferStruct, BYTE * msg, int size)
{
	struct DataTransfer * newMessage;
	struct DataTransfer * orgMessage;
	//
	// Size without data..only the basic message with the IPv6 and UPD (no data) headers..
	//
	int UDP_Size = size + sizeof (struct UDP);
	//
	// Total message size.
	//
	int totalMessageSize = sizeof(struct DataTransfer) + size; 
	//
	// allocate space for the new message;
	//
	BYTE * messagePointer = (BYTE *) malloc(totalMessageSize);
	memset(messagePointer, 0, totalMessageSize);

	newMessage = (struct DataTransfer *)messagePointer;
	orgMessage = (struct DataTransfer *)transferStruct;
	//
	// clear and copy over the IPv6 and UPD data to the new message...
	//
	newMessage->_Header._Id = orgMessage->_Header._Id;
	newMessage->_Header._Origin = orgMessage->_Header._Origin;
	newMessage->_Header._Length = (UINT16)(totalMessageSize-sizeof(struct Header));

	newMessage->_Spacer = orgMessage->_Spacer;

	newMessage->_IPv6_Header._Header[0] = 0x60;
	newMessage->_IPv6_Header._NextHeader = 17; // This is value for the UDP header..
	newMessage->_IPv6_Header._HopLimit = orgMessage->_IPv6_Header._HopLimit;
	newMessage->_IPv6_Header._PayloadLength = (UINT16)UDP_Size;
	memcpy(newMessage->_IPv6_Header._DestinationAddress, orgMessage->_IPv6_Header._DestinationAddress, 16);
	memcpy(newMessage->_IPv6_Header._SourceAddress, orgMessage->_IPv6_Header._SourceAddress, 16);
	
	//newMessage->_UDP_Message._CRC = 0xABCD;  // just put something here for wireshark..
	newMessage->_UDP_Message._SourcePort = orgMessage->_UDP_Message._SourcePort;
	newMessage->_UDP_Message._DestinationPort = orgMessage->_UDP_Message._DestinationPort;
	newMessage->_UDP_Message._Length = (UINT16)UDP_Size;
	memcpy(&newMessage->_UDP_Message._Data[0], msg, size);
	
	newMessage->_UDP_Message._CRC = GenerateCRC16Udp(newMessage);

	return newMessage;
}

