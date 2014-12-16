#pragma once
#include "../UtilityLibrary/Message.h"

class TLV : public Message
{
protected:
	UINT16 _Type;
public:
	TLV(void);
	TLV(int length);
	TLV(int type, int length);
	TLV(const TLV & tlv);

	virtual int Read_TLV(BYTE * data, int offset);
	virtual Message * Write_TLV();

	virtual TextString ToString() { TextString temp; return temp; }

	virtual ~TLV(void);
};

