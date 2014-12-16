#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Status_Message.h"

Status_Message::Status_Message(void)
{
	InitializeData();
}

Status_Message::Status_Message(BYTE id)
{
	InitializeData();
	_StatusMessage._Header._Id = id;
	_StatusMessage._Header._Origin = 0;
}

Status_Message::Status_Message(BYTE * msg, int offset)
{
	ReadGenericMessage(&_StatusMessage, sizeof(StatusMessage), msg, offset);
}

Status_Message::Status_Message(const Status_Message & msg): HostMessage(msg)
{
	memcpy(&_StatusMessage, & msg._StatusMessage, sizeof(struct StatusMessage));
}

Status_Message::~Status_Message(void)
{
}

void Status_Message::InitializeData()
{
	memset(&_StatusMessage, 0, sizeof(struct StatusMessage));
};

HostMessage * Status_Message::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = new Status_Message(data, offset);
	return msg;
}

TextString Status_Message::ToString()
{
	TextString temp;
	temp.Format("Status_Message: Id=   0x%2.2X  -  Status: 0x%4.4X\r\n", _StatusMessage._Header._Id,_StatusMessage._Status);
	return temp;
}
