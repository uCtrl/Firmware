#pragma GCC diagnostic ignored "-Wwrite-strings"
#include "Message.h"
//#include "LogFile.h"

extern Serial usbSerial;

Message::Message()
{
	_MessageSize = 0;
	_Message = NULL;
}

Message::Message(int size)
{
	_MessageSize = size;
	_Message = new BYTE[size];
}


Message::Message(int size, unsigned char * message )
{
	_MessageSize = size;
	_Message = new unsigned char[size];
	if (_Message == NULL)
	{
		usbSerial.printf("memory allocation fail");
//		LogFile::Write("Unable to allocate memory in Message class constructor: Size= %d\r\n", size);
	}
	else
	{
		memcpy(_Message, message, size);
	}
}
Message::Message(int size, unsigned char * message, int offset )
{
	_MessageSize = size;
	_Message = new unsigned char[size];
	if (_Message == NULL)
	{
//		LogFile::Write("Unable to allocate memory in Message class constructor: Size= %d\r\n", size);
	}
	else
	{
		memcpy(_Message, & message[offset], size);
	}
}

Message::Message(int headerSize, unsigned char * header, int msgSize, unsigned char * body)
{
	_MessageSize = headerSize + msgSize;
	_Message = new unsigned char [_MessageSize];
	if (_Message == NULL)
	{
//		LogFile::Write("Unable to allocate memory in Message class constructor: Size= %d\r\n", _MessageSize);
	}
	else
	{
		int offset = 0;
		memcpy(& _Message[offset], header, headerSize);
		offset += headerSize;

		memcpy(&_Message[offset], body, msgSize);
	}
}

Message::Message(Message * header, Message * body)
{
	_MessageSize = header->_MessageSize + body->_MessageSize;
	_Message = new unsigned char [_MessageSize];
	if (_Message == NULL)
	{
//		LogFile::Write("Unable to allocate memory in Message class constructor: Size= %d\r\n", _MessageSize);
	}
	else
	{
		int offset = 0;
		memcpy(& _Message[offset], header->_Message, header->_MessageSize);
		offset += header->_MessageSize;

		memcpy(&_Message[offset], body->_Message, body->_MessageSize);
	}
}

Message::Message(Message * header, Message * crc, Message * body)
{
	_MessageSize = 0;
	if (header != NULL)
	{
		_MessageSize += header->_MessageSize;
	}
	if (crc != NULL)
	{
		_MessageSize += crc->_MessageSize;
	}
	if (body != NULL)
	{
		_MessageSize += body->_MessageSize;
	}
	_Message = new unsigned char [_MessageSize];

	int offset = 0;
	if (header != NULL)
	{
		memcpy(&_Message[offset], header->_Message, header->_MessageSize);
		offset += header->_MessageSize;
	}
	if (crc != NULL)
	{
		memcpy(&_Message[offset], crc->_Message, crc->_MessageSize);
		offset += crc->_MessageSize;
	}
	if (body != NULL)
	{
		memcpy(&_Message[offset], body->_Message, body->_MessageSize);
	}
	return;
}
Message::Message(Message * msg1, Message * msg2, Message * msg3, Message * msg4)
{
	_MessageSize = 0;
	if (msg1 != NULL)
	{
		_MessageSize += msg1->_MessageSize;
	}
	if (msg2 != NULL)
	{
		_MessageSize += msg2->_MessageSize;
	}
	if (msg3 != NULL)
	{
		_MessageSize += msg3->_MessageSize;
	}
	if (msg4 != NULL)
	{
		_MessageSize += msg4->_MessageSize;
	}
	_Message = new unsigned char [_MessageSize];

	int offset = 0;
	if (msg1 != NULL)
	{
		memcpy(&_Message[offset], msg1->_Message, msg1->_MessageSize);
		offset += msg1->_MessageSize;
	}
	if (msg2 != NULL)
	{
		memcpy(&_Message[offset], msg2->_Message, msg2->_MessageSize);
		offset += msg2->_MessageSize;
	}
	if (msg3 != NULL)
	{
		memcpy(&_Message[offset], msg3->_Message, msg3->_MessageSize);
		offset += msg3->_MessageSize;
	}
	if (msg4 != NULL)
	{
		memcpy(&_Message[offset], msg4->_Message, msg4->_MessageSize);
		offset += msg4->_MessageSize;
	}
	return;

}

Message::Message(const Message & msg)
{
	_MessageSize = msg._MessageSize;

	_Message = new unsigned char[_MessageSize];
	if (_Message == NULL)
	{
//		LogFile::Write("Unable to allocate memory in Message class constructor: Size= %d\r\n", _MessageSize);
	}
	else
	{
		memcpy(_Message, msg._Message, _MessageSize);
	}
}

Message::Message(const Message * msg)
{
	_MessageSize = msg->_MessageSize;

	_Message = new unsigned char[_MessageSize];
	if (_Message == NULL)
	{
//		LogFile::Write("Unable to allocate memory in Message class constructor: Size= %d\r\n", _MessageSize);
	}
	else
	{
		memcpy(_Message, msg->_Message, _MessageSize);
	}
}

Message::~Message()
{
	if (_Message != NULL)
	{
		delete [] _Message;
	}
}

int Message::ReadMessage(int length, BYTE * data, int offset)
{
	if (_Message != NULL)
	{
		delete _Message;
		_Message = NULL;
	}
	_MessageSize = length;
	_Message = new BYTE[length];
	memcpy(_Message, & data[offset], length);

	return offset + length;
}

void Message::CreateEmptyMessage(int length)
{
	_MessageSize = length;
	if (_Message != NULL)
	{
		delete _Message;
		_Message = NULL;
	}
	_Message = new BYTE[length];
}
int Message::Concatenate(Message * msg)
{
	if (msg != NULL)
	{
		int newSize = _MessageSize + msg->_MessageSize;
		BYTE * newMessage = new BYTE[newSize];
	
		if (_Message != NULL)
		{
			memcpy(newMessage, _Message, _MessageSize);
		}
		memcpy(&newMessage[_MessageSize], msg->_Message, msg->_MessageSize);
		if (_Message != NULL)
		{
			delete [] _Message;
		}
		_Message = newMessage;
		_MessageSize = newSize;
	}
	return _MessageSize;
}

TextString Message::ToString()
{
	TextString temp;
	if (_Message == NULL || _MessageSize == 0)
	{
		temp.Append("Empty");
	}
	else
	{
		for(int index=0; index < _MessageSize; index++)
		{
			if ((index % 16) == 0)
			{
				temp.AppendFormat("\r\n0x%2.2X ", _Message[index]);
			}
			else
			{
				temp.AppendFormat("%2.2X ", _Message[index]);
			}
		}
	}
	return temp;
}

void Message::ToString(TextString &ts)
{
	if (_Message == NULL || _MessageSize == 0)
	{
		ts.Append("Empty");
	}
	else
	{
		for(int index=0; index < _MessageSize; index++)
		{
			if ((index % 16) == 0)
			{
				ts.AppendFormat("\r\n0x%2.2X ", _Message[index]);
			}
			else
			{
				ts.AppendFormat("%2.2X ", _Message[index]);
			}
		}
	}
}
