#include <stdio.h>
#include "TextString.h"
#include <ctype.h>


TextString::TextString(void)
{
	_Length = 0;
	_Text = NULL;
}

TextString::TextString(const TextString & string)
{
	_Length = string._Length;
	_Text = NULL;
	//
	// Add one for the NULL char
	//
	_Text = new char[_Length+1];
	if (string._Text != NULL)
	{
		strcpy(_Text, string._Text);
	}
	else
	{
		memset(_Text, 0, _Length+1);
	}
}

TextString::TextString(int length)
{
	_Length = length;
	_Text = new char[_Length + 1];
	memset(_Text, 0, _Length+1);
}

TextString::TextString(char * text)
{
	_Length = strlen(text);
	_Text = new char[_Length+1];
	strcpy(_Text, text);
}

TextString::~TextString(void)
{
	Reset();
}

void TextString::Reset(void)
{
	_Length = 0;
	if (_Text != NULL)
	{
		delete [] _Text;
	}
	_Text = NULL;
}
void TextString::ToLower()
{
	if (_Length > 0 && _Text != NULL)
	{
		for(int index = 0; index < _Length; index++)
		{
			int c = tolower(_Text[index]);
			if (c != EOF)
			{
				_Text[index] = (char) c;
			}
		}
	}
}

TextString & TextString::operator = (const TextString & text) 
{
	if (_Text != NULL)
	{
		delete [] _Text;
		_Text = NULL;
	}
	_Length = text._Length;
	_Text = new char[_Length + 1];
	strcpy(_Text, text._Text);
	return *this;
}

TextString & TextString::operator = (const char * text) 
{
	if (_Text != NULL)
	{
		delete [] _Text;
		_Text = NULL;
	}
	_Length = strlen(text);
	_Text = new char[_Length + 1];
	strcpy(_Text, text);
	return *this;
}

bool TextString::operator == (const TextString & other) const
{
	bool status = true;
	if (_Length != other._Length)
	{
		status = false;
	}
	else if (strcmp(_Text, other._Text) != 0)
	{
		status = false;
	}
	return status;
}
void TextString::Append(char * text)
{
	if (text != NULL)
	{
		int len = strlen(text) + _Length;
		char * temp = new char[len+1];
		memset(temp, 0, len+1);

		if (_Text != NULL)
		{
			strcpy(temp, _Text);
			delete [] _Text;
		}
		strcpy(&temp[_Length], text);
		_Text = temp;
		_Length = len;
	}
}

void TextString::AppendFormat(char * format, ...)
{
	TextString tx;
	va_list listPointer;
	va_start(listPointer, format);
	tx._Length = vsnprintf(NULL,0,format, listPointer);
	if (tx._Length > 1)
	{
		tx._Text = new char[tx._Length + 1];
		vsprintf(tx._Text, format, listPointer);
	}

	va_end(listPointer);

	Append(tx._Text);
}

void TextString::Format(char * format, ...)
{
	Reset();

	va_list listPointer;
	va_start(listPointer, format);
	_Length = vsnprintf(NULL,0,format, listPointer);
	if (_Length > 1)
	{
		_Text = new char[_Length + 1];
		vsprintf(_Text, format, listPointer);
	}

	va_end(listPointer);
}

TextString TextString::Tokenize(char * token, int & curPos)
{
	TextString text;
	if (curPos < _Length)
	{
		char * temp = new char[_Length + 1];
		strcpy(temp, &_Text[curPos]);

		char * result = strtok(temp, token);
		if (result == NULL)
		{
			text = &temp[curPos];
			curPos = -1;
		}
		else
		{
			text = result;
			curPos += strlen(result) + 1;
		}
		delete [] temp;
	}
	return text;
}
int TextString::Compare(char * text)
{
	return strcasecmp(_Text, text);
}

