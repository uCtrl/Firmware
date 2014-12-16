#pragma once
#include "Message.h"
#include "UPlcConfigFile.h"

class MessageHeader
{
private:
	BYTE _Id;
	BYTE _Origin;
	
	UINT16 _MessageLength;

protected:	
	UINT16 _Offset;

public:
	MessageHeader(void);
	MessageHeader(const MessageHeader & header);
	MessageHeader(BYTE * data, int offset);

	virtual ~MessageHeader(void);

	virtual UINT16 HeaderLength()
	{ 
		return (sizeof(_Id) + sizeof(_Origin) + sizeof(_MessageLength)); 
	}
	
	MessageHeader & operator = (const BYTE * data);

	virtual Message * MakeHeader();
	virtual int ReadHeader(BYTE * data, int offset);

	virtual BYTE GetId() { return _Id; }
	virtual void SetId(BYTE id) { _Id = id; }

	virtual BYTE GetOrigin() {return _Origin; }
	virtual void SetOrigin(BYTE origin) { _Origin = origin; }
	//
	// The message length includes the 2 CRC values plus the actual message length
	//
	virtual UINT16 GetMessageLength() { return _MessageLength; }
	virtual void SetMessageLength(UINT16 len) { _MessageLength = len; }
};
