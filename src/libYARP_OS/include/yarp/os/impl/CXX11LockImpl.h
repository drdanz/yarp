/*
 * Copyright (C) 2015 Robotics and Cognitive Sciences Department. IIT
 * Authors: Francesco Romano
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_OS_IMPL_CXX11LOCKIMPL_H
#define YARP_OS_IMPL_CXX11LOCKIMPL_H

#include <mutex>

class YARP_OS_impl_API yarp::os::impl::RecursiveLockImpl
{
public:
    RecursiveLockImpl() {}
    RecursiveLockImpl(RecursiveLockImpl&) = delete;
    RecursiveLockImpl& operator= (RecursiveLockImpl&) = delete;

    void lock()
    {
        mutex.lock();
    }

    bool tryLock()
    {
        return mutex.try_lock();
    }

    // increment
    void unlock()
    {
        mutex.unlock();
    }

private:
    std::recursive_mutex mutex;
};

#endif // YARP_OS_IMPL_CXX11LOCKIMPL_H
