#include "HostMessageFactory.h"
#include "HostMessage.h"
#include "Shut_Down_Message.h"
#include "Get_System_Info.h"
#include "Attach.h"
#include "MessageHeader.h"

HostMessageFactory::HostMessageFactory(void)
{
}


HostMessageFactory::~HostMessageFactory(void)
{
	RemoveAll();
}
void HostMessageFactory::AddToFactory(HostMessage * msg)
{
	FactoryKeyValuePair * kvp = new FactoryKeyValuePair(msg->GetKey(), msg);
	Add(kvp);
}
HostMessage * HostMessageFactory::GetHostMessage(BYTE * data, int offset)
{
	MessageHeader header(data, offset);
	//
	// Mask off the bits other than the origin..
	//
	BYTE origin = (header.GetOrigin() & 0x80);
	int key = (header.GetId() << 8) + origin;

	FactoryKeyValuePair * keyValuePair = (FactoryKeyValuePair *)Find((void *)key);
	HostMessage * msg = NULL;
	
	if (keyValuePair != NULL)
	{
		HostMessage * message = keyValuePair->_pHostMessage;
		msg = message->CreateMessage(data, offset);
	}
	return msg;
}

void HostMessageFactory::DeleteData(void * data)
{
	FactoryKeyValuePair * keyValuePair = (FactoryKeyValuePair *) data;
	delete keyValuePair;
}

bool HostMessageFactory::Compare(void * data0, void * data1)
{
	FactoryKeyValuePair * keyValuePair = (FactoryKeyValuePair *) data0;
	UINT32 key = (UINT32) data1;

	return (keyValuePair->_Key == key);
}

FactoryKeyValuePair::FactoryKeyValuePair(UINT32 key, HostMessage * message)
{
	_Key = key;
	_pHostMessage = message;
}

FactoryKeyValuePair::~FactoryKeyValuePair()
{
	if (_pHostMessage != NULL)
	{
		delete _pHostMessage;
		_pHostMessage = NULL;
	}
}
