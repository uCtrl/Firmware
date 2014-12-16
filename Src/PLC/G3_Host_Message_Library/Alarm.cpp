#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Alarm.h"


Alarm::Alarm(void)
{
	_pNSA = NULL;
	InitializeData();
}
Alarm::Alarm(BYTE * data, int offset)
{
	_pNSA = NULL;
	ReadMessage(data, offset);
}
Alarm::Alarm(Alarm & alarm)
{
	if (alarm._pNSA == NULL)
	{
		InitializeData();
	}
	else
	{
		int size = alarm.GetMsgSize();
		_pNSA = (NetworkStatusAlarm *)malloc(size);
		memcpy(_pNSA, alarm._pNSA, size);
	}
}
Alarm::~Alarm(void)
{
	if (_pNSA != NULL)
	{
		free(_pNSA);
		_pNSA = NULL;
	}
}

int Alarm::GetMsgSize()
{
	int size = 0;
	if (_pNSA == NULL)
	{
		InitializeData();
		size = sizeof(NetworkStatusAlarm);
	}
	else
	{
		size = _pNSA->_Header._Length + 4;
	}
	return size;
}
void Alarm::InitializeData()
{
	if (_pNSA != NULL)
	{
		free(_pNSA);
		_pNSA = NULL;
	}
	_pNSA = (NetworkStatusAlarm *) malloc(sizeof(NetworkStatusAlarm));
	memset(_pNSA, 0, sizeof(NetworkStatusAlarm));

	_pNSA->_Header._Id = Alarm_Id;
	_pNSA->_Header._Length = 4 /* crc */ + 4 /* TLV Id and Length */;
	_pNSA->_Header._Origin = 0x00;
	_pNSA->_TLV_Id = 0x0007;
	_pNSA->_TLV_Length = 0;   // no data
}

HostMessage * Alarm::CreateMessage(BYTE * data, int offset)
{
	return new Alarm(data, offset);
}
int Alarm::ReadMessage(BYTE * data, int offset)
{
	InitializeData();
	offset = ReadVariableLengthMessage((void**)&_pNSA, data, offset);
	return offset;
}

void Alarm::CopyTo(HostMessage * msg)
{
	Alarm * copyToMsg = (Alarm *) msg;
	if (copyToMsg->_pNSA != NULL)
	{
		free(copyToMsg->_pNSA);
		copyToMsg->_pNSA = NULL;
	}

	if (_pNSA == NULL)
	{
		copyToMsg->InitializeData();
	}
	else
	{
		int size = GetMsgSize();
		copyToMsg->_pNSA = (NetworkStatusAlarm *) malloc(size);
		memcpy(copyToMsg->_pNSA, _pNSA, size);
	}
}
Message * Alarm::MakeMessage()
{
	return NULL;  //read only message don't bother to write code to make for now..
}
UINT16 Alarm::GetAlarmId()
{
	UINT16 id = 0;
	if (_pNSA != NULL)
	{
		id = _pNSA->_TLV_Id;
	}
	return id;
}
UINT16 Alarm::GetStatus()
{
	UINT16 status = 0;
	if (_pNSA != NULL)
	{
		memcpy(& status, &_pNSA->_Data[0], 2);
	}
	return status;
}
BYTE Alarm::GetSecurityLevel()
{
	BYTE sl = 0;
	if (_pNSA != NULL)
	{
		sl = _pNSA->_Data[2];
	}
	return sl;
}
BYTE Alarm::GetKeyIdMode()
{
	BYTE km = 0;
	if (_pNSA != NULL)
	{
		km = _pNSA->_Data[3];
	}
	return km;
}

UINT16 Alarm::GetKeyIndex()
{
	UINT16 index = 0;
	if (_pNSA != NULL)
	{
		memcpy(& index, &_pNSA->_Data[4], 2);
	}
	return index;
}

UINT16 Alarm::GetPanId()
{
	UINT16 pan = 0;
	if (_pNSA != NULL)
	{
		memcpy(& pan, &_pNSA->_Data[6], 2);
	}
	return pan;
}
UINT16 Alarm::GetAddressMode()
{
	UINT16 addressMode = 0;
	if (_pNSA != NULL)
	{
		memcpy(& addressMode, &_pNSA->_Data[8], 2);
	}
	return addressMode;
}

WordArray Alarm::GetAddress()
{
	WordArray wa;
	UINT16 mode = GetAddressMode();
	if (mode == 2)
	{
		WordArray temp(2, &_pNSA->_Data[10]);
		return temp;
	}
	else if (mode == 3)
	{
		WordArray temp(8, &_pNSA->_Data[10]);
		return temp;
	}
	return wa;
}

TextString Alarm::ToString()
{
	TextString ts;
	ts.Format("G3 Network Alarm: Id= %d\r\n", GetId());
	ts.AppendFormat("   Id:             %d\r\n", GetAlarmId());
	ts.AppendFormat("   Status:         0x%2.2X\r\n", GetStatus());
	ts.AppendFormat("   Security Level: %d\r\n", GetSecurityLevel()); 
	ts.AppendFormat("   Key Id Mode:    %d\r\n", GetKeyIdMode());
	ts.AppendFormat("   Key Index:      %d\r\n", GetKeyIndex());
	ts.AppendFormat("   Pan Id:         0x%4.4X\r\n", GetPanId());
	ts.AppendFormat("   Address Mode:   %d\r\n", GetAddressMode());
	if (GetAddressMode() == 2)
	{
		ts.AppendFormat("   Short Address:  %s\r\n", (char*) GetAddress().ToString());
	}
	else if (GetAddressMode() == 3)
	{
		WordArray wa = GetAddress();
		ts.AppendFormat("   Long Address:   %s\r\n", (char*)wa.ToString());
	}
	return ts;
}
