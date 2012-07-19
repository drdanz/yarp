// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2009 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <yarp/os/all.h>
#include <yarp/os/Os.h>

#include <yarp/name/NameServerManager.h>
#include <yarp/name/BootstrapServer.h>

#include <yarp/yarpserversql/yarpserversql.h>

#include "TripleSourceCreator.h"
#include "NameServiceOnTriples.h"
#include "AllocatorOnTriples.h"
#include "SubscriberOnSql.h"
#include "ComposedNameService.h"
#include "ParseName.h"

using namespace yarp::os;
using namespace yarp::name;
using namespace std;

yarpserversql_API int yarpserver3_main(int argc, char *argv[]) {
    // check if YARP version is sufficiently up to date - there was
    // an important bug fix
    Bottle b("ip 10.0.0.10");
    if (b.get(1).asString()!="10.0.0.10") {
        fprintf(stderr, "Sorry, please update YARP version");
        ::exit(1);
    }

    printf("__   __ _    ____  ____  \n\
\\ \\ / // \\  |  _ \\|  _ \\ \n\
 \\ V // _ \\ | |_) | |_) |\n\
  | |/ ___ \\|  _ <|  __/ \n\
  |_/_/   \\_\\_| \\_\\_|    \n\n");

    Property options;
    options.fromCommand(argc,argv);

    ConstString configFilename = options.check("config",
                                               Value("yarpserver.conf")).asString();
    if (!options.check("config")) {
        configFilename = Network::getConfigFile(configFilename.c_str());
    }
    if (yarp::os::stat(configFilename.c_str())==0) {
        printf("Reading options from %s\n", configFilename.c_str());
        options.fromConfigFile(configFilename.c_str(),false);
    } else {
        printf("Options can be set on command line or in %s\n", configFilename.c_str());
    }

    ConstString dbFilename = options.check("portdb",
                                           Value("ports.db")).asString();
    ConstString subdbFilename = options.check("subdb",
                                              Value("subs.db")).asString();
    ConstString ip = options.check("ip",Value("...")).asString();
    int sock = options.check("socket",Value(10000)).asInt();
    bool cautious = options.check("cautious");
    bool verbose = options.check("verbose");

    printf("Port database: %s (change with \"--portdb newports.db\")\n", 
           dbFilename.c_str());
    printf("Subscription database: %s (change with \"--subdb newsubs.db\")\n", 
           subdbFilename.c_str());
    printf("*** Make sure these database files are not on a shared file system ***\n");
    printf("To clear the name server state, simply stop it, delete these files, and restart.\n\n");
    printf("IP address: %s (change with \"--ip N.N.N.N\")\n", 
           (ip=="...")?"default":ip.c_str());
    printf("Port number: %d (change with \"--socket NNNNN\")\n", sock);
    
    Network yarp;

    bool reset = false;
    if (options.check("ip")||options.check("socket")) {
        fprintf(stderr,"Database needs to be reset, IP or port number set.\n");
        reset = true;
    }

    TripleSourceCreator db;
    TripleSource *pmem = db.open(dbFilename.c_str(),cautious,reset);
    if (pmem == NULL) {
        fprintf(stderr,"Aborting, ports database failed to open.\n");
        return 1;
    }
    if (verbose) {
        pmem->setVerbose(1);
    }

    SubscriberOnSql subscriber;
    if (!subscriber.open(subdbFilename.c_str())) {
        fprintf(stderr,"Aborting, subscription database failed to open.\n");
        return 1;
    }
    if (verbose) {
        subscriber.setVerbose(true);
    }

    Contact contact = 
        Contact::byName("...").addSocket("tcp",ip.c_str(),sock);
    
    BootstrapServer::configFileBootstrap(contact);

    AllocatorConfig config;
    config.minPortNumber = contact.getPort()+2;
    config.maxPortNumber = contact.getPort()+9999;
    AllocatorOnTriples alloc(pmem,config);
    NameServiceOnTriples ns(pmem,&alloc,contact);
    yarp.queryBypass(&ns);
    subscriber.setStore(ns);
    ns.setSubscriber(&subscriber);
    ComposedNameService combo(subscriber,ns);
    NameServerManager name(combo);
    BootstrapServer fallback(name);

    Port server;
    name.setPort(server);
    server.setReaderCreator(name);
    bool ok = server.open(contact,false);
    if (!ok) {
        fprintf(stderr, "Name server failed to open\n");
        return 1;
    }
    printf("\n");

    fallback.start();

    // Repeat registrations for the server and fallback server -
    // these registrations are more complete.
    printf("Registering name server with itself:\n");
    Network::registerContact(contact);
    subscriber.welcome(contact.getName().c_str(),1);
    Network::registerContact(fallback.where());
    subscriber.welcome(fallback.where().getName().c_str(),1);
    ns.goPublic();
    printf("Name server can be browsed at http://%s:%d/\n",
           contact.getHost().c_str(), contact.getPort());
    printf("\nOk.  Ready!\n");
    
    while (true) {
        Time::delay(600);
        printf("Name server running happily\n");
    }
    server.close();

    db.close();

    return 0;
}
