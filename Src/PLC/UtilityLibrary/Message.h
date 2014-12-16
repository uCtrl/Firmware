#pragma once
#include "TextString.h"
#include "UPlcConfigFile.h"

class Message
{
public:
	int _MessageSize;
	unsigned char * _Message;

	Message();
	Message(int size);
	Message(int size, unsigned char * message );
	Message(int size, unsigned char * message, int offset );
	Message(const Message & msg);
	Message(const Message * msg);

	Message(int headerSize, unsigned char * header, int msgSize, unsigned char * body);
	Message(Message * header, Message * body);
	Message(Message * header, Message * crc, Message * body);
	Message(Message * msg1, Message * msg2, Message * msg3, Message * msg4);
	virtual ~Message();

	bool operator == (const Message & other)const
	{
		return (_MessageSize == other._MessageSize && memcmp(_Message, other._Message, _MessageSize));
	}

	int Concatenate(Message * msg);
	int ReadMessage(int length, BYTE * data, int offset);
	void CreateEmptyMessage(int length);

	TextString ToString();
	void ToString(TextString &ts);
};
