#pragma once
#include "HostMessages.h"
#include "HostMessage.h"
#include "ByteArray.h"

class Set_PSK_PIB : public HostMessage
{
private:
	Set_PSK_PIBs _PSK_PIB;
	void * GetHeader () { return & _PSK_PIB; }
	int GetMsgSize() { return sizeof(Set_PSK_PIBs); }


public:
	Set_PSK_PIB(void);
	Set_PSK_PIB(BYTE * msg, int offset);
	Set_PSK_PIB(const Set_PSK_PIB & pib);

	virtual ~Set_PSK_PIB(void);

	virtual TextString ToString();
	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual int GetUniqueId() {return Set_MAC_PSK_PIB_UID;}

	void SetPIB_Id(UINT32 id) { _PSK_PIB._Id = id; }
	UINT16 GetPIB_Index() { return _PSK_PIB._Index; }
	void SetPIB_Index(UINT16 index) { _PSK_PIB._Index = index; }

	BYTE * GetPIB_Key() { return _PSK_PIB._Key; }
	void SetPIB_Key(BYTE * key) { memcpy(_PSK_PIB._Key, key, 16); }
	void SetPIB_Key(TextString ts);
};

class Set_PIB_Reply :	public HostMessage
{
private:
	Set_PIB_Replys _Set_PIB_Reply;
	void * GetHeader() { return & _Set_PIB_Reply; }
	int GetMsgSize() { return sizeof(Set_PIB_Replys); }
	
public:
	Set_PIB_Reply(void);
	Set_PIB_Reply(BYTE * msg, int offset);
	Set_PIB_Reply(const Set_PIB_Reply & msg);

	virtual ~Set_PIB_Reply(void);

	virtual void InitializeData();
	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual int GetUniqueId() {return Set_MAC_PIB_UID + 99;}

	UINT16 Get_Status() { return _Set_PIB_Reply._Status; }
	void Set_Status(UINT16 status) { _Set_PIB_Reply._Status = status; }
};
