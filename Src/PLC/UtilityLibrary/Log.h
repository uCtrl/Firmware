#pragma once
//#include "StringQueue.h"
//#include "CallBackList.h"
#include "CriticalSection.h"
#include "TextString.h"

class Log// : public CallBackList
{
private:
	/*
	static CriticalSection _LogCriticalSection;
	static void WaitForMessage(void * classObject, void * pointer);

	static TextString _LogName;
	static StringQueue _StringQueue;
	static Log * _pLog;
	static UINT32 _LogCount;

	Log(void);
	Log(TCHAR * filename);
	Log(const Log &);
	Log & operator = (const Log &);
	*/
	
public:
	Log(void);
	virtual ~Log(void);

	static void Write(char * format, ...);
	static void DisplayLastError();
	static void Initialize(char * fileName);
	//static int GetCount() { /*return_StringQueue.GetSize();*/ }
};

