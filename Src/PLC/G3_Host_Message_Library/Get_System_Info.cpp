#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Get_System_Info.h"
#include "ByteArray.h"
#include "MessageIds.h"
#include "HostMessage.h"

Get_System_Info_Request::Get_System_Info_Request(void)
{
	InitializeData();
}

Get_System_Info_Request::Get_System_Info_Request(byte * msg, int offset)
{
	ReadGenericMessage(&_GetSystemInfoRequest, sizeof(GetSystemInfoRequest), msg, offset);
}

Get_System_Info_Request::Get_System_Info_Request(const Get_System_Info_Request & msg)
{
	memcpy(&_GetSystemInfoRequest, &msg._GetSystemInfoRequest, sizeof(GetSystemInfoRequest));
}

Get_System_Info_Request::~Get_System_Info_Request(void)
{
}

void Get_System_Info_Request::InitializeData()
{
	memset(&_GetSystemInfoRequest, 0, sizeof(GetSystemInfoRequest));
	_GetSystemInfoRequest._Header._Id = Get_System_Info_Id;
	_GetSystemInfoRequest._Header._Origin = 0x80;
}

HostMessage * Get_System_Info_Request::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = new Get_System_Info_Request(data, offset);
	return msg;
}

TextString Get_System_Info_Request::ToString()
{
	TextString string;
	string.Format("Get System Info Request: Id= 0x%2.2X\r\n\r\n", GetId());
	return string;
}
/////////////////////
//
//
//Get System Info
//
///////////////////
Get_System_Info::Get_System_Info()
{
	InitializeData();
}
Get_System_Info::Get_System_Info(BYTE * msg, int offset)
{
	ReadGenericMessage(&_SystemInfo, sizeof(SystemInfo), msg, offset);
}
Get_System_Info::Get_System_Info(const Get_System_Info & sysInfo)
{
	memcpy(&_SystemInfo, &sysInfo._SystemInfo, sizeof(SystemInfo));
}
Get_System_Info::~Get_System_Info()
{
}

HostMessage * Get_System_Info::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = new Get_System_Info(data, offset);
	return msg;
}

void Get_System_Info::InitializeData()
{
	memset(&_SystemInfo, 0, sizeof(SystemInfo));
	_SystemInfo._Header._Id = Get_System_Info_Id;
	_SystemInfo._Header._Origin = 0x00;
}

//BYTE Get_System_Info::Get_ApplyFlag()
//{
//	BYTE state = 0;
//	if ((_SystemInfo._Flag0 & 0x80) != 0)
//	{
//		state = 1;
//	}
//	return state;
//}
//void Get_System_Info::Set_ApplyFlag(BYTE value)
//{
//	_SystemInfo._Flag0 &= 0x7F;
//	if (value != 0)
//	{
//		_SystemInfo._Flag0 |= 0x80;
//	}
//}
//
//BYTE Get_System_Info::Get_IP_Flag()
//{
//	BYTE state = 0;
//	if ((_SystemInfo._Flag0 & 0x40) != 0)
//	{
//		state = 1;
//	}
//	return state;
//}
//void Get_System_Info::Set_IP_Flag(BYTE value)
//{
//	_SystemInfo._Flag0 &= 0xBF;
//	if (value != 0)
//	{
//		_SystemInfo._Flag0 |= 0x40;
//	}
//}
//
//BYTE Get_System_Info::GetAutoMode()
//{
//	BYTE state = 0;
//	if ((_SystemInfo._Flag0 & 0x20) != 0)
//	{
//		state = 1;
//	}
//	return state;
//}
//void Get_System_Info::SetAutoMode(BYTE value)
//{
//	_SystemInfo._Flag0 &= 0xDF;
//	if (value != 0)
//	{
//		_SystemInfo._Flag0 |= 0x20;
//	}
//}
//
BYTE Get_System_Info::Get_COH_Flag()
{
	BYTE state = 0;
	if ((_SystemInfo._TMR_COH_Flags & 0x08) != 0)
	{
		state = 1;
	}
	return state;
}
void Get_System_Info::Set_COH_Flag(BYTE value)
{
	_SystemInfo._TMR_COH_Flags &= 0xF7;
	if (value != 0)
	{
		_SystemInfo._TMR_COH_Flags |= 0x08;
	}
}
BYTE Get_System_Info::Get_TMR_Flag()
{
	BYTE state = 0;
	if ((_SystemInfo._TMR_COH_Flags & 0x20) != 0)
	{
		state = 1;
	}
	return state;
}
void Get_System_Info::Set_TMR_Flag(BYTE value)
{
	_SystemInfo._TMR_COH_Flags &= 0xDF;
	if (value != 0)
	{
		_SystemInfo._TMR_COH_Flags |= 0x20;
	}
}
//
//BYTE Get_System_Info::Get_PAN_Coord_Flag()
//{
//	BYTE state = 0;
//	if ((_SystemInfo._Flag1 & 0x04) != 0)
//	{
//		state = 1;
//	}
//	return state;
//}
//void Get_System_Info::Set_PAN_Coord_Flag(BYTE value)
//{
//	_SystemInfo._Flag1 &= 0x0B;
//	if (value != 0)
//	{
//		_SystemInfo._Flag1 |= 0x04;
//	}
//}
//BYTE Get_System_Info::Get_MAC_ARQ_Flag()
//{
//	BYTE state = 0;
//	if ((_SystemInfo._Flag1 & 0x01) != 0)
//	{
//		state = 1;
//	}
//	return state;
//}
//void Get_System_Info::Set_MAC_ARQ_Flag(BYTE value)
//{
//	_SystemInfo._Flag1 &= 0x0E;
//	if (value != 0)
//	{
//		_SystemInfo._Flag1 |= 0x01;
//	}
//}
//
//BYTE Get_System_Info::Get_MAC_PAC_Flag()
//{
//	BYTE state = 0;
//	if ((_SystemInfo._Flag1 & 0x02) != 0)
//	{
//		state = 1;
//	}
//	return state;
//}
//void Get_System_Info::Set_MAC_PAC_Flag(BYTE value)
//{
//	_SystemInfo._Flag1 &= 0x0D;
//	if (value != 0)
//	{
//		_SystemInfo._Flag1 |= 0x02;
//	}
//}

TextString Get_System_Info::ToString()
{
	TextString temp;
#ifdef P1901
	temp.Format("P1901.2 System Info:  Id=   %d\r\n", GetId());
#else
	temp.Format("G3 System Info:  Id=   %d\r\n", GetId());
#endif
	temp.AppendFormat("   Software Revision:    %d.%d.%d.%d\r\n", _SystemInfo._Major, _SystemInfo._Minor, _SystemInfo._Revision, _SystemInfo._Build);
//	ByteArray serialNumber(_SystemInfo._SerialNumberLength, _SystemInfo._SerialNumber);
//	temp.AppendFormat("   Serial Number:        %s\r\n", (char *)serialNumber.ToString());
	temp.AppendFormat("   Device Type:          %d\r\n", _SystemInfo._DeviceType);
	temp.AppendFormat("   Device Mode:          %d\r\n", _SystemInfo._DeviceMode);
	temp.AppendFormat("   Hardware Revision:    %d\r\n", _SystemInfo._HardwareRevision);
//	ByteArray eui(sizeof(_SystemInfo._EUI), _SystemInfo._EUI);
//	temp.AppendFormat("   EUI Address:          %s\r\n", (char *)eui.ToString());
	temp.AppendFormat("   Diag Port             %d\r\n", Get_Diag_Port());
	temp.AppendFormat("   Data Port             %d\r\n", Get_Data_Port());
	temp.AppendFormat("   COH Flag              %d\r\n", Get_COH_Flag());
	temp.AppendFormat("   TMR Flag              %d\r\n", Get_TMR_Flag());
//	temp.AppendFormat("   Apply Flag:           %d\r\n", Get_ApplyFlag());
//	temp.AppendFormat("   IP Flag:              %d\r\n", Get_IP_Flag());
//	temp.AppendFormat("   Auto Mode:            %d\r\n", GetAutoMode());
//	temp.AppendFormat("   MAC TX Max Hold PPDU: %d\r\n", _SystemInfo._MAC_RX_Max_Hold_PPDU);
//	temp.AppendFormat("   PRIME MAC Max Conns:  %d\r\n", _SystemInfo._PRIME_MAC_Max_Conns);
//	temp.AppendFormat("   MAC Max RX Q Length:  %d\r\n", _SystemInfo._MAC_Max_RX_Q_Length);
//	temp.AppendFormat("   COH:                  %d\r\n", Get_COH_Flag());
//	temp.AppendFormat("   PAN Coord:            %d\r\n", Get_PAN_Coord_Flag());
//	temp.AppendFormat("   MAC Default ARQ:      %d\r\n", Get_MAC_ARQ_Flag());
//	temp.AppendFormat("   MAC Default PAC:      %d\r\n", Get_MAC_PAC_Flag());
//	temp.AppendFormat("   SecurityProfile:      %d\r\n", _SystemInfo._SecurityProfile);
//	temp.AppendFormat("   Address Type:         0x%4.4X\r\n", _SystemInfo._AddressType);
	ByteArray longaddress(sizeof(_SystemInfo._LongAddress), _SystemInfo._LongAddress);
	temp.AppendFormat("   Long Address:         %s\r\n", (char*)longaddress.ToString());
//	temp.AppendFormat("   Pan Id:               0x%4.4X\r\n", _SystemInfo._PanId);
//	temp.AppendFormat("   Short Address:        0x%4.4X\r\n", _SystemInfo._ShortAddress);
//	temp.AppendFormat("   MAC Segment Length:   %d\r\n\r\n", _SystemInfo._SegmentLength);
	temp.Append("\r\n");
	return temp;
}
