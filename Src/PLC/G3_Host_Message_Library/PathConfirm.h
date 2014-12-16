#pragma once
#include "HostMessage.h"
#include "MessageIds.h"
#include "HostMessages.h"

class PathConfirm :	public HostMessage
{
private:
	PathDiscoverConfirm _PathConfirm;
	void * GetHeader() { return & _PathConfirm; }
	int GetMsgSize();

public:
	PathConfirm(void);
	PathConfirm(BYTE * msg, int offset);
	PathConfirm(const PathConfirm & msg);

	virtual ~PathConfirm(void);

	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual void InitializeData();
	virtual int GetUniqueId()							{ return Path_Discover_Confirm_UID; }
	virtual int ReadMessage(BYTE * data, int offset);
	virtual void CopyTo(HostMessage * msg);	

	UINT16 GetStatus()										{ return _PathConfirm._Status; }
	void SetStatus(UINT16 value)					{ _PathConfirm._Status = value; }

	UINT16 GetShortAddress()							{ return _PathConfirm._ShortAddress; }
	void SetShortAddress(UINT16 value)		{ _PathConfirm._ShortAddress = value; }

	UINT16 GetNumberOfDevices()						{ return _PathConfirm._NumberOfDevices; }
	void SetNumberOfDevices(UINT16 value) { _PathConfirm._NumberOfDevices = value; }

	UINT16 * GetPath()										{ return _PathConfirm._ShortAddressArray; }
	void SetPath(UINT16 * value, UINT16 count)
	{
		_PathConfirm._NumberOfDevices = count;
		memset(_PathConfirm._ShortAddressArray, 0, sizeof(_PathConfirm._ShortAddressArray)*2);
		memcpy(_PathConfirm._ShortAddressArray, value, count);
	}

};

