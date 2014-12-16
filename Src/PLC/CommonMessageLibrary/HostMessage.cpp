#include "HostMessage.h"
#include "HostMessages.h"

void HostMessage::SetORG(BYTE org)
{ 
	SetHeaderORG(org, (Header *)GetHeader());
}

void HostMessage::SetRPY(BYTE rpy) 
{ 
	SetHeaderRPY(rpy, (Header *)GetHeader()); 
}
void HostMessage::SetSEQ(BYTE seq) 
{ 
	SetHeaderSEQ(seq, (Header *)GetHeader());
}

void HostMessage::SetId(BYTE id)
{
	Header * header = (Header *)GetHeader();
	header->_Id= id;
}

BYTE HostMessage::GetORG()
{ 
	return GetHeaderORG((Header *)GetHeader()); 
}

BYTE HostMessage::GetRPY() 
{ 
	return GetHeaderRPY((Header *)GetHeader()); 
}

BYTE HostMessage::GetSEQ() 
{ 
	return GetHeaderSEQ((Header *)GetHeader()); 
}

BYTE HostMessage::GetId()  
{ 
	Header * header = (Header *)GetHeader();
	return header->_Id; 
}
UINT16 HostMessage::GetLength()  
{ 
	Header * header = (Header *)GetHeader();
	return header->_Length; 
}

int HostMessage::ReadMessage(BYTE * data, int offset)
{
	return ReadGenericMessage(GetHeader(), GetMsgSize(), data, offset);
}

Message * HostMessage::MakeMessage()
{
	BYTE * message = MakeGenericMessage(GetHeader(), GetMsgSize());
	Message * msg = new Message();
	msg->_MessageSize = GetMsgSize();
	msg->_Message = message;

	return msg;
}

void HostMessage::CopyTo(HostMessage * msg)
{
	memcpy(msg->GetHeader(), GetHeader(), GetMsgSize());
}
