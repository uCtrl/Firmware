#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "PathRequest.h"
#include "HostMessage.h"
extern int LastDiscoverType;


PathRequest::PathRequest(void)
{
	InitializeData();
}

PathRequest::PathRequest(BYTE * data, int offset)
{
	ReadGenericMessage(&_PathRequest, sizeof(_PathRequest), data, offset);
}

PathRequest::PathRequest(const PathRequest & pr)
{
	memcpy(&_PathRequest, & pr._PathRequest, sizeof(_PathRequest));
}

PathRequest::~PathRequest(void)
{
}

void PathRequest::InitializeData()
{
	memset(& _PathRequest, 0, sizeof(PathDiscoverRequest));
	_PathRequest._Header._Id = Discover_Id;
	_PathRequest._Header._Origin = 0x80;
	_PathRequest._DiscoverType = PathDiscover;
	_PathRequest._ShortAddress = 0;
	LastDiscoverType = PathDiscover;
}

HostMessage * PathRequest::CreateMessage(BYTE * data, int offset)
{
	return new PathRequest(data, offset);
}

TextString PathRequest::ToString()
{
	TextString temp;
	temp.Format("Path Discover_Request: Id=   %d\r\n", GetId());
	temp.AppendFormat("   Discover Type: %d\r\n", _PathRequest._DiscoverType);
	temp.AppendFormat("   Short Address: 0x%4.4X\r\n\r\n", _PathRequest._ShortAddress);
	return temp;
}
