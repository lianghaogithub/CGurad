#ifndef _UVFS_LOCK_H_
#define _UVFS_LOCK_H_
#include <windows.h>

namespace OCLS
{
class CLock
{
public:
    CLock(void)
    {
        spinCount_ = 0;
        ::InitializeCriticalSection(&criticalSection_);
    }

    ~CLock(void)
    {
        ::DeleteCriticalSection(&criticalSection_);
    }

    void Enter(void)
    {
        ::EnterCriticalSection(&criticalSection_);
        spinCount_++;
    }

    void Leave(void)
    {
        spinCount_--;
        ::LeaveCriticalSection(&criticalSection_);
    }

private:
    CRITICAL_SECTION criticalSection_;
    long spinCount_;
};


template <class T>
class CGuard
{
public:
    CGuard(T& lockObject) : lockObject_(lockObject)
    {
        lockObject_.Enter();
    }

    ~CGuard(void)
    {
        lockObject_.Leave();
    }

private:
    T& lockObject_;
};
}
#endif
