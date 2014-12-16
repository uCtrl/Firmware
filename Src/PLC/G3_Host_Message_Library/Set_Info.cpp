#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Set_Info.h"
#include "MessageIds.h"
#include "Get_System_Info.h"

ByteArray * ToneMasks[] = 
	{
		new ByteArray(14, 0x17, 0x24, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 0 =  Cenelec A36
		new ByteArray(14, 0x17, 0x24, 0xFF, 0xFF, 0x00, 0xF8, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 1 = Cenelec A25
		new ByteArray(14, 0x3F, 0x10, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 2 = Cenelec B
		new ByteArray(14, 0x3F, 0x1A, 0xFF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 3 = Cenelec BC
		new ByteArray(14, 0x3F, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 4 = Cenelec BCD
		                 
		new ByteArray(14, 0x21, 0x24, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 5 = FCC Low Band
		new ByteArray(14, 0x45, 0x24, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 6 = FCC High Band
		new ByteArray(14, 0x21, 0x48, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00 ), // 7 = FCC Full Band.

		new ByteArray(14, 0x3B, 0XA4, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 8 = ????
		new ByteArray(14, 0x1F, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00 ), // 9 = ????
		new ByteArray(14, 0x21, 0x0C, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 10= FCC ARIB 12 
		new ByteArray(14, 0x21, 0x18, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ), // 11= FCC ARIB 24
		new ByteArray(14, 0x21, 0x36, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00 )  // 12= FCC ARIB 54
	};
//
//
//
//
//
Set_TX_Info::Set_TX_Info(void)
{
	InitializeData();
}

Set_TX_Info::Set_TX_Info(BYTE * msg, int offset)
{
	ReadGenericMessage(&_SetInfo_TX, sizeof(SetInfo_TX), msg, offset);
}

Set_TX_Info::Set_TX_Info(const Set_TX_Info & sti)
{
	memcpy(&_SetInfo_TX, &sti._SetInfo_TX, sizeof(SetInfo_TX));
}

Set_TX_Info::~Set_TX_Info(void)
{
}
int Set_TX_Info::GetMsgSize()
{
	int size = sizeof(_SetInfo_TX);
	return size;
}

void Set_TX_Info::InitializeData()
{
	memset(&_SetInfo_TX, 0, sizeof(SetInfo_TX));
	_SetInfo_TX._Header._Id = Set_Info_Id;
	_SetInfo_TX._Header._Origin = 0x80;
	_SetInfo_TX._InfoType = 0x002;
	
	_SetInfo_TX._InfoLength = 18;
	_SetInfo_TX._TX_Level = 16;
	memcpy(_SetInfo_TX._ToneMask, ToneMasks[Cenelec_A_36]->_Array, sizeof(_SetInfo_TX._ToneMask));
}

HostMessage * Set_TX_Info::CreateMessage(BYTE * msg, int offset)
{
	HostMessage * hm = new Set_TX_Info(msg, offset);
	Set_TX_Info * sti = (Set_TX_Info *) hm;
	//
	//If this is really a RX or Vendor type delete the old message and create the RX Info
	//
	if (sti->_SetInfo_TX._InfoType == 0x0003)
	{
		delete hm;
		hm = new Set_RX_Info(msg, offset);
	}
	else if (sti->_SetInfo_TX._InfoType == 0x0004)
	{
		delete hm;
		hm = new Set_VendorProduct_Info(msg, offset);
	}
	return hm;
}

TextString Set_TX_Info::ToString()
{
	TextString temp;
#ifdef P1901
	temp.Format("P1901.2 Set TX Info: Id=   0x%2.2X\r\n", GetId());
#else
	temp.Format("G3 Set TX Info: Id=   0x%2.2X\r\n", GetId());
#endif
	temp.AppendFormat("   Type:        %d\r\n", _SetInfo_TX._InfoType);
	temp.AppendFormat("   Length:      %d\r\n", _SetInfo_TX._InfoLength);
	temp.AppendFormat("   Band Select: %d\r\n", Get_Band_Select());
	temp.AppendFormat("   COH:         %d\r\n", Get_COH_Flag());
	temp.AppendFormat("   TMR::        %d\r\n", Get_TMR_Flag());
	temp.AppendFormat("   TX Level:    %d\r\n", Get_TX_Level());

	int toneMaskSize = 14;
	ByteArray ba(toneMaskSize, Get_ToneMask());
	temp.AppendFormat("   ToneMask:    %s\r\n\r\n", (char *)ba.ToString());
	return temp;
}

void Set_TX_Info::Set_COH_Flag(BYTE value)
{
	_SetInfo_TX._Flags &= 0xF7;
	if (value != 0)
	{
		_SetInfo_TX._Flags |= 0x08;
	}
}

void Set_TX_Info::Set_Band_Select(BYTE value)
{
	_SetInfo_TX._Flags &= 0xBF;
	if (value != 0)
	{
		_SetInfo_TX._Flags |= 0x40;
	}
}
	
void Set_TX_Info::Set_TMR_Flag(BYTE value)
{
	_SetInfo_TX._Flags &= 0xFE;
	if (value != 0)
	{
		_SetInfo_TX._Flags |= 0x01;
	}
}
void Set_TX_Info::Set_ToneMask(BYTE * toneMask)
{
	memcpy(&_SetInfo_TX._ToneMask, toneMask, sizeof(_SetInfo_TX._ToneMask));
}
/*

Set Info RX message

*/
Set_RX_Info::Set_RX_Info(void)
{
	InitializeData();
}

Set_RX_Info::Set_RX_Info(BYTE * msg, int offset)
{
	ReadGenericMessage(&_SetInfo_RX, sizeof(SetInfo_RX), msg, offset);
}

Set_RX_Info::Set_RX_Info(const Set_RX_Info & msg)
{
	memcpy(&_SetInfo_RX, &msg._SetInfo_RX, sizeof(SetInfo_RX));
}

Set_RX_Info::~Set_RX_Info(void)
{

}
int Set_RX_Info::GetMsgSize()
{
	int size = sizeof(_SetInfo_RX);
	return size;
}

HostMessage * Set_RX_Info::CreateMessage(BYTE * msg, int offset)
{
	HostMessage * hm = new Set_RX_Info(msg, offset);
	Set_RX_Info * sri = (Set_RX_Info *) hm;
	//
	//If this is really a TX or Vendor type delete the old message and create the RX Info
	//
	if (sri->_SetInfo_RX._InfoType == 0x0002)
	{
		delete hm;
		hm = new Set_TX_Info(msg, offset);
	}
	else if (sri->_SetInfo_RX._InfoType == 0x0004)
	{
		delete hm;
		hm = new Set_VendorProduct_Info(msg, offset);
	}
	return hm;
}

void Set_RX_Info::InitializeData()
{
	memset(&_SetInfo_RX, 0, sizeof(SetInfo_RX));

	_SetInfo_RX._Header._Id = Set_Info_Id;
	_SetInfo_RX._Header._Origin = 0x80;

	_SetInfo_RX._InfoType = 0x0003;

	_SetInfo_RX._InfoLength = 18;
	Set_ROBO_Flag(1);
	Set_AGC_Flag(1);
	Set_ToneMask(ToneMasks[Cenelec_A_36]->_Array);
}

TextString Set_RX_Info::ToString()
{
	TextString temp;
#ifdef P1901
	temp.Format("P1901.2 Set RX Info: Id=   0x%2.2X\r\n", GetId());
#else
	temp.Format("G3 Set RX Info: Id=   0x%2.2X\r\n", GetId());
#endif
	temp.AppendFormat("   Type:        %d\r\n", _SetInfo_RX._InfoType);
	temp.AppendFormat("   Length:      %d\r\n", _SetInfo_RX._InfoLength);
	temp.AppendFormat("   Band Select: %d\r\n", Get_Band_Select());
	temp.AppendFormat("   COH:         %d\r\n", Get_COH_Flag());
	temp.AppendFormat("   BLI:         %d\r\n", Get_BLI_Flag());
	temp.AppendFormat("   ROBO:        %d\r\n", Get_ROBO_Flag());
	temp.AppendFormat("   AGC:         %d\r\n", Get_AGC_Flag());
	temp.AppendFormat("   Gain Value:  %d\r\n", Get_GainValue());
	int toneMaskSize = 14;

	ByteArray ba(toneMaskSize, _SetInfo_RX._ToneMask);
	temp.AppendFormat("   ToneMask:    %s\r\n\r\n", (char*)ba.ToString());
	return temp;
}
void Set_RX_Info::Set_COH_Flag(BYTE value)
{
	_SetInfo_RX._Flags &= 0x07;
	if (value != 0)
	{
		_SetInfo_RX._Flags |= 0x08;
	}
}
void Set_RX_Info::Set_BLI_Flag(BYTE value)
{
	_SetInfo_RX._Flags &= 0x0B;
	if (value != 0)
	{
		_SetInfo_RX._Flags |= 0x04;
	}
}

void Set_RX_Info::Set_Band_Select(BYTE value)
{
	_SetInfo_RX._Flags &= 0xBF;
	if (value != 0)
	{
		_SetInfo_RX._Flags |= 0x40;
	}
}
void Set_RX_Info::Set_ROBO_Flag(BYTE value)
{
	_SetInfo_RX._Flags &= 0x0D;
	if (value != 0)
	{
		_SetInfo_RX._Flags |= 0x02;
	}
}
void Set_RX_Info::Set_AGC_Flag(BYTE value)
{
	_SetInfo_RX._Flags &= 0x0E;
	if (value != 0)
	{
		_SetInfo_RX._Flags |= 0x01;
	}
}
void Set_RX_Info::Set_ToneMask(BYTE * toneMask)
{
	memcpy(&_SetInfo_RX._ToneMask, toneMask, sizeof(_SetInfo_RX._ToneMask));
}
/*

Set Info Vendor/Product Id message

*/
Set_VendorProduct_Info::Set_VendorProduct_Info(void)
{
	InitializeData();
}

Set_VendorProduct_Info::Set_VendorProduct_Info(BYTE * msg, int offset)
{
	ReadGenericMessage(&_SetInfo_VendorProductId, sizeof(SetInfo_VendorProductId), msg, offset);
}

Set_VendorProduct_Info::Set_VendorProduct_Info(const Set_VendorProduct_Info & msg)
{
	memcpy(&_SetInfo_VendorProductId, &msg._SetInfo_VendorProductId, sizeof(SetInfo_VendorProductId));
}

Set_VendorProduct_Info::~Set_VendorProduct_Info(void)
{

}

HostMessage * Set_VendorProduct_Info::CreateMessage(BYTE * msg, int offset)
{
	HostMessage * hm = new Set_VendorProduct_Info(msg, offset);
	Set_VendorProduct_Info * svpi = (Set_VendorProduct_Info *) hm;
	//
	//If this is really a TX or RX type delete the old message and create the RX Info
	//
	if (svpi->_SetInfo_VendorProductId._InfoType == 0x0002)
	{
		delete hm;
		hm = new Set_TX_Info(msg, offset);
	}
	else if (svpi->_SetInfo_VendorProductId._InfoType == 0x0003)
	{
		delete hm;
		hm = new Set_RX_Info(msg, offset);
	}
	return hm;
}

void Set_VendorProduct_Info::InitializeData()
{
	memset(&_SetInfo_VendorProductId, 0, sizeof(SetInfo_VendorProductId));

	_SetInfo_VendorProductId._Header._Id = Set_Info_Id;
	_SetInfo_VendorProductId._Header._Origin = 0x80;

	_SetInfo_VendorProductId._InfoType = 0x0004;
	_SetInfo_VendorProductId._InfoLength = 18;
}

TextString Set_VendorProduct_Info::ToString()
{
	TextString temp;
	temp.Format("Set Vendor and Product Ids=   0x%2.2X\r\n", GetId());
	temp.AppendFormat("   Type:       %d\r\n", _SetInfo_VendorProductId._InfoType);
	temp.AppendFormat("   Length:     %d\r\n", _SetInfo_VendorProductId._InfoLength);
	temp.AppendFormat("   Vendor Id:  %d\r\n", Get_VendorId());
	temp.AppendFormat("   Product Id: %s\r\n\r\n", (char*)Get_ProductId());
	return temp;
}

void Set_VendorProduct_Info::Set_ProductId(CHAR * productId)
{
	if (strlen(productId) <= 15)
	{
		memset(_SetInfo_VendorProductId._ProductId, 0, 16);
		strcpy(_SetInfo_VendorProductId._ProductId, productId);
	}
}
