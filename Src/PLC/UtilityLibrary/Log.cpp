
#include <iostream>
#include <fstream>
#include "mbed.h"
#include "Log.h"
#include "CriticalSection.h"

//using namespace std;

extern Serial usbSerial;

//extern volatile bool Shutdown;
//extern HANDLE ShutdownEventHandle;

//CriticalSection Log::_LogCriticalSection;
//StringQueue Log::_StringQueue;
//TextString Log::_LogName;
//Log * Log::_pLog = new Log();
//UINT32 Log::_LogCount = 0;;

Log::Log(void)
{
	//_StringQueue.AddCallBack(this, WaitForMessage);
}


Log::~Log(void)
{/*
	//
	// Wait until the queue is empty to go away..
	//
	while(_StringQueue.GetSize() > 0)
	{
		Sleep(1000);
	}
	_StringQueue.RemoveCallBack(this, WaitForMessage);
	*/
}

void Log::DisplayLastError()
{
	/*
	DWORD dw;
	LPTSTR buf = NULL;
	DWORD lastError = GetLastError();

	dw = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM, 0, lastError, 0, (LPTSTR) & buf, 0, 0);
	Write("Last error= %d: %s\r\n", lastError, buf);
	LocalFree(buf);
	*/
}

void Log::Write(char * format, ...)
{
	va_list listPointer;
	va_start(listPointer, format);
	int len = vsnprintf(NULL, 0, format, listPointer);
	char * text = NULL;
	if (len > 1)
	{
		text = new char[len+1];
		vsprintf(text, format, listPointer);
	}

	va_end(listPointer);

	TextString ts;
	ts.Format("%s", text);

	usbSerial.printf(ts);
	if (text != NULL)
	{
		delete [] text;
	}
}
/*
void Log::WaitForMessage(void * classObject, void * pointer)
{

	Log * pLog = (Log*)classObject;
	char * msg = (char *)pointer;

	_LogCriticalSection.Lock();
	//
	// Write time to dos and file..
	//
	cout << msg << flush;

	if (_LogName.GetLength() > 0)
	{
		if (Log::_LogCount == 0 && CommandLineArguments::CmdArg()->Exists("resetlog"))
		{
			ofstream LogFile;
			LogFile.open(pLog->_LogName, ios::trunc | ios::out);
			if (LogFile.is_open() == true)
			{
				LogFile << msg << flush;
				LogFile.close();
			}
		}
		else
		{
			ofstream LogFile;
			LogFile.open(pLog->_LogName,ios::app | ios::out);
			if (LogFile.is_open())
			{
				LogFile << msg << flush;
				LogFile.close();
			}
		}
		Log::_LogCount++;
	}
	//
	// Call any callbacks added by the user..
	//
	pLog->Execute(msg);
	
	_LogCriticalSection.UnLock();

	return;

}
*/

void Log::Initialize(char * fileName)
{
	//_LogName = fileName;
}
