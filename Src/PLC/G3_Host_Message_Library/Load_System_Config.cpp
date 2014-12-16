#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Load_System_Config.h"
#include "HostMessages.h"
#include "MessageIds.h"
#include "ByteArray.h"


Load_System_Config::Load_System_Config(void)
{
	InitializeData();
}

Load_System_Config::Load_System_Config(BYTE * data, int offset)
{
	InitializeData();
	ReadLoadSystemConfigurationMessage(&_Configuration, data, offset);
}

Load_System_Config::Load_System_Config(const Load_System_Config & msg)
{
	InitializeData();
	if (msg._Configuration._Port != NULL)
	{
		memcpy(Get_PortDesignation(), msg._Configuration._Port, sizeof(_Configuration._Port));
	}
	if (msg._Configuration._SystemConfig != NULL)
	{
		memcpy(Get_SystemConfg(), msg._Configuration._SystemConfig, sizeof(_Configuration._SystemConfig));
	}
	
	if (msg._Configuration._G3_Config != NULL)
	{
		memcpy(Get_G3Config(), msg._Configuration._G3_Config, sizeof(_Configuration._G3_Config));
	}
}

Load_System_Config::~Load_System_Config(void)
{
	FreeSystemConfigMessage(&_Configuration);
}

int Load_System_Config::GetMsgSize()
{
	int size = sizeof(Header) + sizeof(CRC_Header);
	if (_Configuration._Port != NULL)
	{
		size += sizeof(PortDesignation);
	}
	if (_Configuration._SystemConfig != NULL)
	{
		size += sizeof(SystemConfig);
	}
	if (_Configuration._G3_Config != NULL)
	{
		size += sizeof(G3Configuration);
	}
	size += (size & 1);

	return size;
}
Message * Load_System_Config::MakeMessage()
{
	int size = GetMsgSize();
	BYTE * data = MakeLoadSystemConfigurationMessage(&_Configuration);
	Message * msg = new Message();
	msg->_MessageSize = size;
	msg->_Message = data;
	return msg;
}

TextString Load_System_Config::ToString()
{
	TextString temp;
	temp.Format("Load System Config: Id= 0x%2.2X\r\n", GetId());
	if (_Configuration._Port != NULL)
	{
		char * diagPort = NULL;
		if (Get_DiagPort() == SCI_A)
		{
			diagPort = "   Diag Port:            SCI-A\r\n";
		}
		else
		{
			diagPort = "   Diag Port:            SCI-B\r\n";
		}
		char * dataPort;
		if (Get_DataPort() == SCI_A)
		{
			dataPort = "   Data Port:            SCI-A\r\n";
		}
		else
		{
			dataPort = "   Data Port:            SCI-B\r\n";
		}
		temp.Append(diagPort);
		temp.Append(dataPort);
	}
	if (_Configuration._SystemConfig != NULL)
	{
		temp.AppendFormat("   Device Mode:          %d\r\n", this->Get_DeviceMode());
//		temp.AppendFormat("   Serial Number Len:    %d\r\n", Get_SerialNumberLength());
//		ByteArray ba(Get_SerialNumberLength(), Get_SerialNumber());
//		temp.AppendFormat("   Serial Number:        %s\r\n", (char*)ba.ToString());
		//ByteArray eui(6, Get_EUI());
//		temp.AppendFormat("   EUI:                  %s\r\n", (char *)eui.ToString());
//		temp.AppendFormat("   Reply                 %d\r\n", Get_RPY_Flag());
//		temp.AppendFormat("   Auto Mode             %d\r\n", Get_Auto_Flag());
	
	}
	if (_Configuration._G3_Config != NULL)
	{
//		temp.AppendFormat("   PAN Coord Flag:       %d\r\n", Get_PAN_Coord_Flag());
		ByteArray la(8, Get_LongAddress());
		temp.AppendFormat("   LongAddress:          %s\r\n", (char*)la.ToString());
//		temp.AppendFormat("   PAN Id:               0x%4.4X\r\n", Get_PAN_Id());
//		temp.AppendFormat("   Short Address:        0x%4.4X\r\n", Get_ShortAddress());
//		temp.AppendFormat("   Segment Length:       %d\r\n", Get_MAC_SegmentSize());
	}
	temp.Append("\r\n");
	return temp;
}

void Load_System_Config::InitializeData(void)
{
	InitializeSystemConfigurationMessage(&_Configuration);
}

HostMessage * Load_System_Config::CreateMessage(BYTE * data, int offset)
{
	HostMessage * msg = new Load_System_Config(data, offset);
	return msg;
}
//
// Accessors
//
//
// Port Designation accessors
//
PortDesignation * Load_System_Config::Get_PortDesignation()
{
	if (_Configuration._Port == NULL)
	{
		_Configuration._Port = (PortDesignation*) malloc(sizeof(PortDesignation));
		memset(_Configuration._Port, 0, sizeof(PortDesignation));
	}
	return _Configuration._Port;
}


BYTE Load_System_Config::Get_DataPort()
{
	BYTE port = 0;
	if (_Configuration._Port != NULL)
	{
		port = (_Configuration._Port->_Port & 0x03);
	}
	return port;
}
BYTE Load_System_Config::Get_DiagPort()
{
	BYTE port = 0;
	if (_Configuration._Port != NULL)
	{
		port = ((_Configuration._Port->_Port & 0x0C) >> 2);
	}
	return port;
}
void Load_System_Config::Set_DataPort(BYTE value)
{
	Get_PortDesignation()->_Port &= 0x0C;
	if (value != 0)
	{
		_Configuration._Port->_Port |= 0x01;
	}
}
void Load_System_Config::Set_DiagPort(BYTE value)
{
	Get_PortDesignation()->_Port &= 0x03;
	if (value != 0)
	{
		Get_PortDesignation()->_Port |= 0x04;
	}
}
//
// System config accessors.
//
SystemConfig * Load_System_Config::Get_SystemConfg()
{
	if (_Configuration._SystemConfig == NULL)
	{
		_Configuration._SystemConfig = (SystemConfig *) malloc(sizeof(SystemConfig));
		memset(_Configuration._SystemConfig, 0, sizeof(SystemConfig));
	}
	return _Configuration._SystemConfig;
}

//UINT16 Load_System_Config::Get_SerialNumberLength()
//{
//	UINT16 length = 0;
//	if (_Configuration._SystemConfig != NULL)
//	{
//		length = _Configuration._SystemConfig->_SerialNumberLength;
//	}
//	return length;
//}
//BYTE * Load_System_Config::Get_SerialNumber()
//{
//	BYTE * serialNumber = 0;
//	if (_Configuration._SystemConfig != NULL)
//	{
//		serialNumber = _Configuration._SystemConfig->_SerialNumber;
//	}
//	return serialNumber;
//}
//
//BYTE * Load_System_Config::Get_EUI()
//{
//	BYTE * eui = 0;
//	if (_Configuration._SystemConfig != NULL)
//	{
//		eui = _Configuration._SystemConfig->_EUI;
//	}
//	return eui;
//}

BYTE Load_System_Config::Get_DeviceMode()
{
	BYTE mode = 0;
	if (_Configuration._SystemConfig != NULL)
	{
		mode = _Configuration._SystemConfig->_DeviceMode;
	}
	return mode;
}

//BYTE Load_System_Config::Get_RPY_Flag()
//{
//	BYTE rpy = 0;
//	if (_Configuration._SystemConfig != NULL)
//	{
//		rpy = _Configuration._SystemConfig->_Flags & 0x80;
//	}
//	return rpy;
//}
//
//BYTE Load_System_Config::Get_Auto_Flag()
//{
//	BYTE flag = 0;
//	if (_Configuration._SystemConfig != NULL)
//	{
//		flag = _Configuration._SystemConfig->_Flags & 0x20;
//	}
//	return flag;
//}
//
//
//void Load_System_Config::Set_SerialNumberLength(UINT16 value)
//{
//	Get_SystemConfg()->_SerialNumberLength = value;
//}
//
//void Load_System_Config::Set_SerialNumber(BYTE * value)
//{
//	memcpy(Get_SystemConfg()->_SerialNumber, value, 16);
//}
//
//void Load_System_Config::Set_EUI(BYTE * value)
//{
//	memcpy(Get_SystemConfg()->_EUI, value, 6);
//}
void Load_System_Config::Set_DeviceMode(BYTE value)
{
	Get_SystemConfg()->_DeviceMode = value;
}
//void Load_System_Config::Set_RPY_Flag(BYTE value)
//{
//	Get_SystemConfg()->_Flags &= 0x7F;
//	if (value != 0)
//	{
//		Get_SystemConfg()->_Flags |= 0x80;
//	}
//}
//void Load_System_Config::Set_Auto_Flag(BYTE value)
//{
//	Get_SystemConfg()->_Flags &= 0xDF;
//	if (value != 0)
//	{
//		Get_SystemConfg()->_Flags |= 0x20;
//	}
//}
//
// G3 Config accessors
//
G3Configuration * Load_System_Config::Get_G3Config()
{
	if (_Configuration._G3_Config == NULL)
	{
		_Configuration._G3_Config = (G3Configuration *) malloc(sizeof(G3Configuration));
		memset(_Configuration._G3_Config, 0, sizeof(G3Configuration));
	}
	return _Configuration._G3_Config;
}

//BYTE Load_System_Config::Get_PAN_Coord_Flag()
//{
//	BYTE flag = 0;
//	if (_Configuration._G3_Config != NULL)
//	{
//		flag = _Configuration._G3_Config->_PAN_Coord_Flag;
//	}
//	return flag;
//}
BYTE * Load_System_Config::Get_LongAddress()
{
	BYTE * address = 0;
	if (_Configuration._G3_Config != NULL)
	{
		address = _Configuration._G3_Config->_LongAddress;
	}
	return address;
}

//UINT16 Load_System_Config::Get_PAN_Id()
//{
//	UINT16 value= 0;
//	if (_Configuration._G3_Config != NULL)
//	{
//		value = _Configuration._G3_Config->_PAN_Id;
//	}
//	return value;
//}
//UINT16 Load_System_Config::Get_ShortAddress()
//{
//	UINT16 value= 0;
//	if (_Configuration._G3_Config != NULL)
//	{
//		value = _Configuration._G3_Config->_ShortAddress;
//	}
//	return value;
//}
//
//UINT16 Load_System_Config::Get_MAC_SegmentSize()
//{
//	UINT16 value= 0;
//	if (_Configuration._G3_Config != NULL)
//	{
//		value = _Configuration._G3_Config->_SegementSize;
//	}
//	return value;
//}
//
//
//void Load_System_Config::Set_PAN_Coord_Flag(BYTE value)
//{
//	Get_G3Config()->_PAN_Coord_Flag &= 0xEF;
//	if (value != 0)
//	{
//		Get_G3Config()->_PAN_Coord_Flag |= 0x10;
//	}
//}

void Load_System_Config::Set_LongAddress(BYTE * value)
{
	memcpy(Get_G3Config()->_LongAddress, value, 8);
}
//void Load_System_Config::Set_PAN_Id(UINT16 value)
//{
//	Get_G3Config()->_PAN_Id = value;
//}
//void Load_System_Config::Set_ShortAddress(UINT16 value)
//{
//	Get_G3Config()->_ShortAddress = value;
//}
//void Load_System_Config::Set_MAC_SegmentSize(UINT16 value)
//{
//	Get_G3Config()->_SegementSize = value;
//}

void Load_System_Config::CopyTo(HostMessage *msg )
{
	Load_System_Config * copyToMsg = (Load_System_Config *) msg;
	FreeSystemConfigMessage(& copyToMsg->_Configuration);

	if (_Configuration._Port != NULL)
	{
		memcpy(copyToMsg->_Configuration._Port, Get_PortDesignation(), sizeof(_Configuration._Port));
	}
	if (_Configuration._SystemConfig != NULL)
	{
		memcpy(copyToMsg->_Configuration._SystemConfig, Get_SystemConfg(), sizeof(_Configuration._SystemConfig));
	}
	
	if (_Configuration._G3_Config != NULL)
	{
		memcpy(copyToMsg->_Configuration._G3_Config, Get_G3Config(), sizeof(_Configuration._G3_Config));
	}
}
