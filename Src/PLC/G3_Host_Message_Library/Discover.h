#pragma once

#include "HostMessages.h"
#include "HostMessage.h"
#include "MessageIds.h"

//static int LastDiscoverType;

class Discover_Network_Request :	public HostMessage
{
private:
	DiscoverNetworkRequest _DiscoverNetworkRequest;
	void * GetHeader() { return & _DiscoverNetworkRequest; }
	int GetMsgSize() { return sizeof(DiscoverNetworkRequest); }

public:
	Discover_Network_Request(void);
	Discover_Network_Request(BYTE * msg, int offset);
	Discover_Network_Request(const Discover_Network_Request & msg);

	virtual ~Discover_Network_Request(void);

	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual void InitializeData();
	virtual int GetUniqueId() {return Discover_UID + 1;}

	DiscoverType GetDiscoverType() { return (DiscoverType)_DiscoverNetworkRequest._DiscoverType; }
	BYTE GetDuration() { return _DiscoverNetworkRequest._Duration; }

	void SetDuration(BYTE duration) { _DiscoverNetworkRequest._Duration = duration; }
};

class  Discover_Network_Confirm :	public HostMessage
{
private:
	DiscoverNetworkConfirm *_pDiscoverNetworkConfirm;
	DiscoverNetworkConfirmVersion54 *_pDiscoverNetworkConfirmVersion54;

	void * GetHeader();
	int GetMsgSize();

public:
	Discover_Network_Confirm(void);
	Discover_Network_Confirm(BYTE * msg, int offset);

	Discover_Network_Confirm(Discover_Network_Confirm & msg);

	virtual ~Discover_Network_Confirm(void);

	virtual HostMessage * CreateMessage(BYTE * data, int offset);
	virtual TextString ToString();
	virtual void InitializeData();
	virtual int GetUniqueId() {return Discover_UID + 2;}
	virtual void CopyTo(HostMessage *msg );
	//
	// Not supporting the creation of this message..
	// This message is only read from the PLC..
	//
	Message * MakeMessage() { return NULL; }
	
	UINT16 GetStatus();
	UINT16 Get_PAN_Count();
	PAN_Description * Get_PAN(int index);
	PAN_DescriptionVersion54 * Get_PAN_Version54(int index);
};
