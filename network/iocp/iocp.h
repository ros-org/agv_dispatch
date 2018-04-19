﻿#ifndef IOCP_H
#define IOCP_H

#include "../timer/timer.h"

#ifdef WIN32
namespace qyhnetwork
{

//! post callback
using _OnPostHandler = std::function<void()>;

enum POST_COM_KEY
{
    PCK_USER_DATA,
};

class EventLoop :public std::enable_shared_from_this<EventLoop>
{
public:
    EventLoop(){_io = NULL;}
    ~EventLoop(){}

    bool initialize();
    void runOnce(bool isImmediately = false);
    inline unsigned long long createTimer(unsigned int delayms, _OnTimerHandler &&handle, bool useSystemTime = true)
    {
        return _timer.createTimer(delayms, std::move(handle), useSystemTime);
    }
    inline unsigned long long createTimer(unsigned int delayms, const _OnTimerHandler &handle, bool useSystemTime = true)
    {
        return _timer.createTimer(delayms, handle, useSystemTime);
    }
    inline bool cancelTimer(unsigned long long timerID)
    {
        return _timer.cancelTimer(timerID);
    }

    //handle: std::function<void()>
    //switch initiative, in the multi-thread it's switch call thread simultaneously.
    void post(_OnPostHandler &&h);
private:
    std::string logSection();
public:
    HANDLE _io;
    Timer _timer;
};
using EventLoopPtr = std::shared_ptr<EventLoop>;
}

#endif

#endif // IOCP_H