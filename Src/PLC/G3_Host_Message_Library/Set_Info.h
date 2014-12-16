#pragma once
#include "HostMessages.h"
#include "HostMessage.h"
#include "ByteArray.h"

enum ToneMaskId
{
	Cenelec_A_36 = 0,
	Cenelec_A_25,
	Cenelec_B,
	Cenelec_BC,
	Cenelec_BCD,
	FCC_Low_Band,
	FCC_High_Band,
	FCC_Full_Band
};
extern ByteArray * ToneMasks[];

class Set_TX_Info : public HostMessage
{
private:
	SetInfo_TX _SetInfo_TX;
	void * GetHeader() { return & _SetInfo_TX; }
	int GetMsgSize();

public:
	Set_TX_Info(void);
	Set_TX_Info(BYTE * msg, int offset);
	Set_TX_Info(const Set_TX_Info &info);
	
	virtual ~Set_TX_Info(void);

	virtual TextString ToString();
	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual int GetUniqueId() {return Set_Info_UID+1;}

	BYTE Get_Band_Select() { return _SetInfo_TX._Flags & 0x40; }
	void Set_Band_Select(BYTE value);

	BYTE Get_COH_Flag() { return (_SetInfo_TX._Flags & 0x08); }
	void Set_COH_Flag(BYTE value);
	
	BYTE Get_TMR_Flag() { return (_SetInfo_TX._Flags & 0x01); }
	void Set_TMR_Flag(BYTE value);
	
	BYTE Get_Modulation() { return _SetInfo_TX._Modulation; }
	void Set_Modulation(BYTE modulation) { _SetInfo_TX._Modulation = modulation;}
	
	UINT16 Get_TX_Level() { return _SetInfo_TX._TX_Level; }
	void Set_TX_Level(UINT16 value) { _SetInfo_TX._TX_Level = value; }

	BYTE * Get_ToneMask() { return _SetInfo_TX._ToneMask; }
	void Set_ToneMask(BYTE * toneMask);
};

class Set_RX_Info : public HostMessage
{
private:
	SetInfo_RX _SetInfo_RX;
	void * GetHeader() { return & _SetInfo_RX; }
	int GetMsgSize();

public:
	Set_RX_Info(void);
	Set_RX_Info(BYTE * msg, int offset);
	Set_RX_Info(const Set_RX_Info & info);
	
	virtual ~Set_RX_Info(void);

	virtual TextString ToString();
	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual int GetUniqueId() {return Set_Info_UID+2;}

	BYTE Get_Band_Select() { return _SetInfo_RX._Flags & 0x40; }
	void Set_Band_Select(BYTE value);

	BYTE Get_COH_Flag() { return (_SetInfo_RX._Flags & 0x08); }
	void Set_COH_Flag(BYTE value);

	BYTE Get_BLI_Flag() { return (_SetInfo_RX._Flags & 0x04); }
	void Set_BLI_Flag(BYTE value);

	BYTE Get_ROBO_Flag() { return (_SetInfo_RX._Flags & 0x02); }
	void Set_ROBO_Flag(BYTE value);

	BYTE Get_AGC_Flag() { return (_SetInfo_RX._Flags & 0x01); }
	void Set_AGC_Flag(BYTE value);

	UINT16 Get_GainValue() { return _SetInfo_RX._GainValue; }
	void Set_GainValue(BYTE value) { _SetInfo_RX._GainValue = value; }

	BYTE * Get_ToneMask() { return _SetInfo_RX._ToneMask; }
	void Set_ToneMask(BYTE * toneMask);

};

class Set_VendorProduct_Info : public HostMessage
{
private:
	SetInfo_VendorProductId _SetInfo_VendorProductId;
	void * GetHeader() { return & _SetInfo_VendorProductId; }
	int GetMsgSize() { return sizeof(_SetInfo_VendorProductId); }

public:
	Set_VendorProduct_Info(void);
	Set_VendorProduct_Info(BYTE * msg, int offset);
	Set_VendorProduct_Info(const Set_VendorProduct_Info & info);
	
	virtual ~Set_VendorProduct_Info(void);

	virtual TextString ToString();
	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual int GetUniqueId() {return Set_Info_UID+3;}

	UINT16 Get_VendorId() { return _SetInfo_VendorProductId._VendorId; }
	void Set_VendorId(UINT16 value) { _SetInfo_VendorProductId._VendorId = value; }

	CHAR * Get_ProductId() { return _SetInfo_VendorProductId._ProductId; }
	void Set_ProductId(CHAR * product_id);
};
