#include "Set_PSK_PIB.h"
#pragma GCC diagnostic ignored "-Wwrite-strings"


Set_PSK_PIB::Set_PSK_PIB(void)
{
	InitializeData();
}

Set_PSK_PIB::Set_PSK_PIB(BYTE * msg, int offset)
{
	ReadGenericMessage(&_PSK_PIB, sizeof(Set_PSK_PIBs), msg, offset);
}

Set_PSK_PIB::Set_PSK_PIB(const Set_PSK_PIB & pib)
{
	memcpy(& _PSK_PIB, & pib._PSK_PIB, sizeof(Set_PSK_PIBs));
}
Set_PSK_PIB::~Set_PSK_PIB(void)
{
}

void Set_PSK_PIB::InitializeData()
{
	memset(& _PSK_PIB, 0, sizeof(Set_PSK_PIBs));
	_PSK_PIB._Header._Id = Set_MAC_PIB_Id;
	_PSK_PIB._Header._Origin = 0x80;
	_PSK_PIB._Id = 0;
	_PSK_PIB._Index = 0;
	_PSK_PIB._Length = 16;
}
HostMessage * Set_PSK_PIB::CreateMessage(BYTE * data, int offset)
{
	HostMessage * hm = new Set_PSK_PIB(data, offset);
	return hm;
}
TextString Set_PSK_PIB::ToString()
{
	TextString temp;
	temp.Format("Set Key: Id = 0x%8.8X\r\n", _PSK_PIB._Id);
	temp.AppendFormat("   Index: %d\r\n", _PSK_PIB._Index);
	ByteArray ba(16, _PSK_PIB._Key);
	temp.AppendFormat("   Key:  %s\r\n\r\n", (char*)ba.ToString());
	return temp;
}

void Set_PSK_PIB::SetPIB_Key(TextString ts)
{
	ByteArray ba(ts);
	memset(_PSK_PIB._Key, 0, 16);
	int size = 16;
	if (ba._Size < 16)
	{
		size = ba._Size;
	}
	memcpy(_PSK_PIB._Key, ba._Array, size);
}

Set_PIB_Reply::Set_PIB_Reply(void)
{
	InitializeData();
}

Set_PIB_Reply::Set_PIB_Reply(BYTE * msg, int offset)
{
	ReadGenericMessage(&_Set_PIB_Reply, sizeof(Set_PIB_Replys), msg, offset);
}
Set_PIB_Reply::Set_PIB_Reply(const Set_PIB_Reply & msg)
{
	memcpy(&_Set_PIB_Reply, &msg._Set_PIB_Reply, sizeof(Set_PIB_Replys));
}

Set_PIB_Reply::~Set_PIB_Reply(void)
{
}

HostMessage * Set_PIB_Reply::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = new Set_PIB_Reply(data, offset);
	return msg;
}

TextString Set_PIB_Reply::ToString()
{
	TextString temp;
	temp.Format("Set PIB Reply: Id= %d - Status: 0x%4.4X\r\n\r\n", GetId(), _Set_PIB_Reply._Status);
	return temp;
}

void Set_PIB_Reply::InitializeData()
{
	memset(&_Set_PIB_Reply, 0, sizeof(Set_PIB_Replys));
	_Set_PIB_Reply._Header._Id = Set_MAC_PIB_Id;
	_Set_PIB_Reply ._Header._Origin = 0x00;
};
