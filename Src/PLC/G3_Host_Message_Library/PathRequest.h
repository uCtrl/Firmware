#pragma once

#include "HostMessage.h"
#include "MessageIds.h"
#include "HostMessages.h"

class PathRequest :	public HostMessage
{
private:
	PathDiscoverRequest _PathRequest;
	void * GetHeader() { return & _PathRequest; }
	int GetMsgSize() { return sizeof(PathDiscoverRequest); }

public:
	PathRequest(void);
	PathRequest(BYTE * msg, int offset);
	PathRequest(const PathRequest & msg);

	virtual ~PathRequest(void);

	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual void InitializeData();
	virtual int GetUniqueId() {return Path_Discover_UID; }
	
	void SetShortAddress(UINT16 value)	{ _PathRequest._ShortAddress = value; }
	UINT16 GetShortAddress()						{ return _PathRequest._ShortAddress; }
};

