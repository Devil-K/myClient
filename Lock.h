#ifndef H_LOCK_H
#define H_LOCK_H

#include <windows.h>

typedef class LockObject{
public:
	LockObject(CRITICAL_SECTION* lock)
		:cs(lock){
		InitializeCriticalSection(cs);
	}

	~LockObject(){
		DeleteCriticalSection(cs);
	}
private:
	CRITICAL_SECTION* cs;
}CSObject;

typedef class Lock{
public:
	Lock(CRITICAL_SECTION* lock)
		:cs(lock){
		EnterCriticalSection(cs);
		}
	~Lock(){  //  Îö¹¹º¯Êý
		LeaveCriticalSection(cs);
	}
private:
	CRITICAL_SECTION* cs;
}CSLock;

#endif//H_LOCK_H