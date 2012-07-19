// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
* Copyright (C) 2007-2009 RobotCub Consortium
* CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
*/

#include <stdio.h>
#include <signal.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/Network.h>
#include <yarp/os/impl/Logger.h>
#include <yarp/os/impl/RunReadWrite.h>

#ifndef YARP_HAS_ACE
#ifndef __APPLE__
#include <wait.h>
#else
#include <sys/wait.h>
#endif
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#endif

#include <yarp/os/impl/RunCheckpoints.h>

#if defined(WIN32)
static void sigbreakHandler(int sig)
{
    CHECK_ENTER("sigbreakHandler")
    raise(SIGINT);
    CHECK_EXIT()
}
#endif

/////////////////////////////////////

static void wSigintHandler(int sig);

int RunWrite::loop(yarp::os::ConstString& uuid)
{
    CHECK_ENTER("RunWrite::loop")

    yarp::os::impl::Logger::get().setVerbosity(-1);

    signal(SIGINT,wSigintHandler);
    signal(SIGTERM,wSigintHandler);

#if defined(WIN32)
    signal(SIGBREAK,(ACE_SignalHandler)sigbreakHandler);
#else
    signal(SIGHUP,SIG_IGN);
#endif

    CHECKPOINT()

    mWPortName=uuid+"/stdout";

    if (!mWPort.open(mWPortName.c_str()))
    {
        YARP_ERROR(yarp::os::impl::Logger::get(),"RunWrite: could not open output port\n");

        CHECK_EXIT()
        return 1;
    }

    static const yarp::os::ConstString TOPIC("topic:/");
    yarp::os::Network::connect(mWPortName.c_str(),(TOPIC+uuid+"/topic_i").c_str());

    CHECKPOINT()

    while (!feof(stdin)) 
    {
        std::string txt=getStdin();

        if (!feof(stdin)) 
        {
            if (txt[0]>=32 || txt[0]=='\n' || txt[0]=='\r' || txt[0]=='\t' || txt[0]=='\0') 
            {
                yarp::os::Bottle bot;
                bot.addString(txt.c_str());
                //bot.fromString(txt.c_str());
                mWPort.write(bot);
            }
            else
            {
                break;
            }
        }
    }

    CHECKPOINT()

    mWPort.interrupt();

    CHECKPOINT()

    mWPort.close();

    CHECKPOINT()

    yarp::os::NetworkBase::unregisterName(mWPortName.c_str());

    CHECK_EXIT()

    return 0;
}

void RunWrite::close()
{
    CHECK_ENTER("RunWrite::close")
    mWPort.interrupt();
    CHECKPOINT()
    mWPort.close();
    CHECKPOINT()
    yarp::os::NetworkBase::unregisterName(mWPortName.c_str());
    CHECK_EXIT()
    exit(0);
}

std::string RunWrite::getStdin() 
{
    CHECK_ENTER("RunWrite::getStdin")

    std::string txt="";
    char buf[2048];

    char *result=ACE_OS::fgets(buf,sizeof(buf),stdin);
    if (result!=NULL) 
        txt+=buf;

    CHECK_EXIT()
    
    return txt;
}

yarp::os::Port RunWrite::mWPort;
yarp::os::ConstString RunWrite::mWPortName;

static void wSigintHandler(int sig)
{
    CHECK_ENTER("wSigintHandler")
    RunWrite::close();
    CHECK_EXIT()
}

///////////////////////////////////////////

static void rSigintHandler(int sig);

int RunRead::loop(yarp::os::ConstString& uuid)
{
    CHECK_ENTER("RunRead::loop")

    yarp::os::impl::Logger::get().setVerbosity(-1);

    signal(SIGINT,rSigintHandler);
    signal(SIGTERM,rSigintHandler);

#if defined(WIN32)
    signal(SIGBREAK,(ACE_SignalHandler)sigbreakHandler);
#else
    signal(SIGHUP,SIG_IGN);
#endif

    CHECKPOINT()

    mRPortName=uuid+"/stdin";
    mRPort.setReader(*this);

    if (!mRPort.open(mRPortName.c_str()))
    {
        YARP_ERROR(yarp::os::impl::Logger::get(),"RunRead: could not open input port\n");
        CHECK_EXIT()
        return 1;
    }

    CHECKPOINT()

    static const yarp::os::ConstString TOPIC("topic:/");
    yarp::os::Network::connect((TOPIC+uuid+"/topic_o").c_str(),mRPortName.c_str());

    CHECKPOINT()
    mDone.wait();
    CHECKPOINT()

    mRPort.interrupt();
    CHECKPOINT()
    mRPort.close();
    CHECKPOINT()
    yarp::os::NetworkBase::unregisterName(mRPortName.c_str());
    CHECK_EXIT()

    return 0;
}

bool RunRead::read(yarp::os::ConnectionReader& reader) 
{
    CHECK_ENTER("RunRead::read")
    if (!reader.isValid())
    {
        CHECK_EXIT()
        return false;
    }
    CHECKPOINT()

    yarp::os::Bottle bot;

    if (bot.read(reader))
    {
        if (bot.size()==1)
        {
            ACE_OS::printf("%s",bot.get(0).asString().c_str());
            ACE_OS::fflush(stdout);
            CHECK_EXIT()
            return true;
        }

        if (bot.size()==2 && bot.get(0).isInt() && bot.get(1).isString()) 
        {
            if (bot.get(0).asInt()!=1) 
            {
                ACE_OS::printf("%s",bot.get(1).asString().c_str());
                ACE_OS::fflush(stdout);
            }
        } 
        else
        {
            //ACE_OS::printf("%s\n", bot.toString().c_str());
            ACE_OS::printf("%s",bot.get(0).asString().c_str());
            ACE_OS::fflush(stdout);
        }

        CHECK_EXIT()
        return true;
    }

    CHECK_EXIT()
    return false;
}

std::string RunRead::getStdin() 
{
    CHECK_ENTER("RunRead::getStdin")

    std::string txt="";
    char buf[2048];

    char *result=ACE_OS::fgets(buf,sizeof(buf),stdin);
    if (result!=NULL) 
          txt+=buf;

    CHECK_EXIT()
    return txt;
}

yarp::os::Semaphore RunRead::mDone(0);
yarp::os::Port RunRead::mRPort;
yarp::os::ConstString RunRead::mRPortName;

static void rSigintHandler(int sig)
{
    CHECK_ENTER("rSigintHandler")
    RunRead::close();
    CHECK_EXIT()
}

///////////////////////////////////////////

static void rwSigintHandler(int sig);

#if !defined(WIN32)
static void sighupHandler(int sig);
#endif

int RunReadWrite::loop(yarp::os::ConstString &uuid)
{
    CHECK_ENTER("RunReadWrite::loop")

    yarp::os::impl::Logger::get().setVerbosity(-1);

    signal(SIGINT,rwSigintHandler);
    signal(SIGTERM,rwSigintHandler);

#if defined(WIN32)
    signal(SIGBREAK,(ACE_SignalHandler)sigbreakHandler);
#else
    signal(SIGHUP,sighupHandler);
#endif

    CHECKPOINT()

    mUUID=uuid;
    mWPortName=uuid+"/stdio:o";
    mRPortName=uuid+"/stdio:i";

    mRPort.setReader(*this);

    if (!mRPort.open(mRPortName.c_str()))
    {
        YARP_ERROR(yarp::os::impl::Logger::get(),"RunReadWrite: could not open input port\n");
        CHECK_EXIT()
        return 1;
    }

    if (!mWPort.open(mWPortName.c_str()))
    {
        CHECKPOINT()
        YARP_ERROR(yarp::os::impl::Logger::get(),"RunReadWrite: could not open output port\n");
        CHECKPOINT()
        mRPort.close();
        CHECKPOINT()
        yarp::os::NetworkBase::unregisterName(mRPortName.c_str());
        CHECK_EXIT()
        return 1;
    }

    CHECKPOINT()

    static const yarp::os::ConstString TOPIC("topic:/");
    yarp::os::Network::connect(mWPortName.c_str(),(TOPIC+uuid+"/topic_o").c_str());
    yarp::os::Network::connect((TOPIC+uuid+"/topic_i").c_str(),mRPortName.c_str());

    CHECKPOINT()

    while (!feof(stdin)) 
    {
        std::string txt=getStdin();

        if (!feof(stdin)) 
        {
            if (txt[0]>=32 || txt[0]=='\n' || txt[0]=='\r' || txt[0]=='\0' || txt[0]=='\t') 
            {
                yarp::os::Bottle bot;
                //bot.fromString(txt.c_str());
                bot.addString(txt.c_str());
                CHECKPOINT()
                mWPort.write(bot);
                CHECKPOINT()
            }
            else
            {
                break;
            }
        }
    }

    CHECKPOINT()

    close();

    CHECK_EXIT()

    return 0;
}

void RunReadWrite::close()
{
    CHECK_ENTER("RunReadWrite::close")

#if !defined(WIN32)
    mDone.wait();
    CHECKPOINT()
        
    if (!mClosed) 
    {
        mClosed=true;
#endif  

        static const yarp::os::ConstString TOPIC("topic:/");
        yarp::os::Network::disconnect((mUUID+"/stdout").c_str(),(TOPIC+mUUID+"/topic_i").c_str());
        yarp::os::Network::disconnect((TOPIC+mUUID+"/topic_i").c_str(),(mUUID+"/stdio:i").c_str());
        yarp::os::Network::disconnect((mUUID+"/stdio:o").c_str(),(TOPIC+mUUID+"/topic_o").c_str());
        yarp::os::Network::disconnect((TOPIC+mUUID+"/topic_o").c_str(),(mUUID+"/stdin").c_str());

        CHECKPOINT()

        mRPort.interrupt();
        mRPort.close();
        yarp::os::NetworkBase::unregisterName(mRPortName.c_str());

        CHECKPOINT()

        mWPort.interrupt();
        mWPort.close();
        yarp::os::NetworkBase::unregisterName(mWPortName.c_str());

        CHECKPOINT()

        int ret=0;
        ret=system((yarp::os::ConstString("yarp topic --remove ")+mUUID+"/topic_i").c_str());

        CHECKPOINT()

        if (ret!=0)
            YARP_LOG_ERROR("call to system returned error");

        ret=system((yarp::os::ConstString("yarp topic --remove ")+mUUID+"/topic_o").c_str());

        CHECKPOINT()

        if (ret!=0)
            YARP_LOG_ERROR("call to system returned error");

#if !defined(WIN32)
    }
    CHECKPOINT()
    mDone.post();
#endif

    CHECK_EXIT()

    exit(0);
}

bool RunReadWrite::read(yarp::os::ConnectionReader& reader) 
{
    CHECK_ENTER("RunReadWrite::read")
    
    if (!reader.isValid())
    { 
        CHECK_EXIT()
        return false;
    }

    yarp::os::Bottle bot;

    if (bot.read(reader))
    {
        if (bot.size()==1)
        {
            ACE_OS::printf("%s",bot.get(0).asString().c_str());
            ACE_OS::fflush(stdout);
            CHECK_EXIT()
            return true;
        }

        if (bot.size()==2 && bot.get(0).isInt() && bot.get(1).isString()) 
        {
            if (bot.get(0).asInt()!=1) 
                {
                    ACE_OS::printf("%s",bot.get(1).asString().c_str());
                    ACE_OS::fflush(stdout);
                }
        }
        else
        {
            ACE_OS::printf("%s\n", bot.toString().c_str());
            ACE_OS::fflush(stdout);
        }

        CHECK_EXIT()
        return true;
    }

    CHECK_EXIT()
    return false;
}

std::string RunReadWrite::getStdin() 
{
    CHECK_ENTER("RunReadWrite::getStdin")

    std::string txt="";
    char buf[2048];

    char *result=ACE_OS::fgets(buf,sizeof(buf),stdin);
    if (result!=NULL) 
        txt+=buf;

    CHECK_EXIT()

    return txt;
}

bool RunReadWrite::mClosed=false;
yarp::os::Semaphore RunReadWrite::mDone(1);
yarp::os::Port RunReadWrite::mRPort;
yarp::os::Port RunReadWrite::mWPort;
yarp::os::ConstString RunReadWrite::mRPortName;
yarp::os::ConstString RunReadWrite::mWPortName;
yarp::os::ConstString RunReadWrite::mUUID;

static void rwSigintHandler(int sig)
{
    CHECK_ENTER("rwSigintHandler")
    RunReadWrite::close();
    CHECK_EXIT()
}

#if !defined(WIN32) && !defined(WIN64)
static void sighupHandler(int sig)
{
    CHECK_ENTER("sighupHandler")
    RunReadWrite::close();
    CHECK_EXIT()
}
#endif
