#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "RouteRequest.h"
#include "HostMessage.h"

extern int LastDiscoverType;

RouteRequest::RouteRequest(void)
{
	InitializeData();
}

RouteRequest::RouteRequest(BYTE * data, int offset)
{
	ReadGenericMessage(&_RouteRequest, sizeof(_RouteRequest), data, offset);
}

RouteRequest::RouteRequest(const RouteRequest & rr)
{
	memcpy(&_RouteRequest, & rr._RouteRequest, sizeof(_RouteRequest));
}

RouteRequest::~RouteRequest(void)
{
}

void RouteRequest::InitializeData()
{
	memset(& _RouteRequest, 0, sizeof(RouteDiscoverRequest));
	_RouteRequest._Header._Id = Discover_Id;
	_RouteRequest._Header._Origin = 0x80;
	_RouteRequest._MaxHops = 7;
	_RouteRequest._DiscoverType = RouteDiscover;
	_RouteRequest._ShortAddress = 0;
	LastDiscoverType = RouteDiscover;

}

HostMessage * RouteRequest::CreateMessage(BYTE * data, int offset)
{
	return new RouteRequest(data, offset);
}

TextString RouteRequest::ToString()
{
	TextString temp;
	temp.Format("Route Discover_Request: Id=   %d\r\n", GetId());
	temp.AppendFormat("   Discover Type: %d\r\n", _RouteRequest._DiscoverType);
	temp.AppendFormat("   Max Hops:      %d\r\n", _RouteRequest._MaxHops);
	temp.AppendFormat("   Service Node:  0x%4.4X\r\n\r\n", _RouteRequest._ShortAddress);
	return temp;
}
