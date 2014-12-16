#pragma once
#include "HostMessage.h"
#include "LinkedList.h"

class HostMessageFactory;

class FactoryKeyValuePair
{
	friend HostMessageFactory;

	UINT32 _Key;
	HostMessage * _pHostMessage;

public:
	FactoryKeyValuePair(UINT32 key, HostMessage * message);
	~FactoryKeyValuePair();
};

class HostMessageFactory : public LinkedList
{
protected:
	
public:
	HostMessageFactory(void);
	virtual ~HostMessageFactory(void);

	virtual HostMessage * GetHostMessage(BYTE * data, int offset);
	virtual void AddToFactory(HostMessage * msg);

	virtual void DeleteData(void * data);
	virtual bool Compare(void * data0, void * data1);
};

