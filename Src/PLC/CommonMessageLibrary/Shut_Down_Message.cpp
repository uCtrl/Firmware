#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Shut_Down_Message.h"
#include "MessageIds.h"

/*
	virtual Message * MakeMessage();
*/

Shut_Down_Message::Shut_Down_Message(void)
{
	InitializeData();
}

Shut_Down_Message::Shut_Down_Message(BYTE * data, int offset)
{
	ReadGenericMessage(&_ShutDownMessage, sizeof(ShutDownMessage),data, offset);
}


Shut_Down_Message::Shut_Down_Message(const Shut_Down_Message & msg)
{
	memcpy(&_ShutDownMessage, &msg._ShutDownMessage, sizeof(struct ShutDownMessage));
}


Shut_Down_Message::~Shut_Down_Message(void)
{
}

HostMessage * Shut_Down_Message::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = new Shut_Down_Message(data, offset);
	return msg;
}

void Shut_Down_Message::InitializeData()
{
	memset(&_ShutDownMessage, 0, sizeof(ShutDownMessage));
	_ShutDownMessage._Header._Id = Shut_Down_Id;
	//
	// Reset the origin to the host..
	//
	_ShutDownMessage._Header._Origin = 0x80;
	_ShutDownMessage._ResetType = SoftReset;
}

TextString Shut_Down_Message::ToString()
{
	TextString temp;
	temp.Format("Shut Down Message: Id=   %d  - Reset Type: %d\r\n\r\n", _ShutDownMessage._Header._Id, _ShutDownMessage._ResetType);
	return temp;
}
