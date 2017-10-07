/*
 * Copyright (C) 2012-2014  iCub Facility, Istituto Italiano di Tecnologia
 * Authors: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
 *          Marco Randazzo          <marco.randazzo@iit.it>
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#ifndef YARP_OS_IMPL_LOGIMPL_H
#define YARP_OS_IMPL_LOGIMPL_H

#include <yarp/os/Log.h>

class yarp::os::impl::LogImpl
{
public:
    LogImpl(const char *file,
            const unsigned int line,
            const char *func);

    static void print_callback(yarp::os::Log::LogType t,
                               const char *msg,
                               const char *file,
                               const unsigned int line,
                               const char *func);

    static void forward_callback(yarp::os::Log::LogType t,
                                 const char *msg,
                                 const char *file,
                                 const unsigned int line,
                                 const char *func);

    const char *file;
    const unsigned int line;
    const char *func;

    static std::ofstream ftrc; /// Used by yTrace()
    static std::ofstream fout; /// Used by yDebug() and yInfo()
    static std::ofstream ferr; /// Used by yWarning(), yError() and yFatal()

    static bool colored_output;
    static bool verbose_output;
    static bool trace_output;
    static bool debug_output;
    static bool forward_output;
};


#endif // YARP_OS_IMPL_LOGIMPL_H
