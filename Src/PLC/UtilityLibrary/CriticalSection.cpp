#include "CriticalSection.h"


CriticalSection::CriticalSection(void):semaphore(1)
{
}


CriticalSection::~CriticalSection(void)
{
}

void CriticalSection::Lock(void)
{
	semaphore.wait();
}

void CriticalSection::UnLock(void)
{
	semaphore.release();
}
