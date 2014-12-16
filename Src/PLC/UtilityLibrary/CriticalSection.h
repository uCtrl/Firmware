#pragma once
#include "rtos.h"

class CriticalSection
{
private:
	Semaphore semaphore;
public:
	CriticalSection(void);
	virtual ~CriticalSection(void);

	void Lock();
	void UnLock();
};
