#pragma once
#include "HostMessage.h"
#include "MessageIds.h"
#include "HostMessages.h"

class RouteRequest : public HostMessage
{
private:
	RouteDiscoverRequest _RouteRequest;
	void * GetHeader() { return &_RouteRequest; }
	int GetMsgSize() { return sizeof(RouteDiscoverRequest); }
	
public:
	RouteRequest(void);
	RouteRequest(BYTE * msg, int offset);
	RouteRequest(const RouteRequest & msg);

	virtual ~RouteRequest(void);

	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual void InitializeData();
	virtual int GetUniqueId() { return Route_Discover_UID; };

	void SetShortAddress(UINT16 value)	{ _RouteRequest._ShortAddress = value; }
	UINT16 GetShortAddress()						{ return _RouteRequest._ShortAddress; }

	void SetMaxHops(BYTE value)					{ _RouteRequest._MaxHops = value; }
	BYTE GetMaxHops()										{ return _RouteRequest._MaxHops;  }
};
