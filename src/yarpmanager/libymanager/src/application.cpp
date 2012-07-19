/*
 *  Yarp Modules Manager
 *  Copyright: 2011 (C) Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Ali Paikan <ali.paikan@iit.it>
 * 
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include "application.h"

/**
 * Class  ModuleInterface
 */
bool ModuleInterface::addPortmap(Portmap &portmap)
{
    portmaps.push_back(portmap);    
    return true;
}

    
bool ModuleInterface::removePortmap(Portmap& portmap)
{
    PortmapIterator itr = findPortmap(portmap);
    if(itr == portmaps.end()) 
        return true;
    portmaps.erase(itr);
    return true;
}


PortmapIterator ModuleInterface::findPortmap(Portmap& portmap) 
{
    PortmapIterator itr;
    for(itr=portmaps.begin(); itr<portmaps.end(); itr++) 
        if ((*itr) == portmap)
            return itr;
    return portmaps.end();
}



/**
 * Class Application
 */
Application::Application(void) : Node(APPLICATION) 
{
    clear();
}


Application::Application(const char* szName) : Node(APPLICATION) 
{
    clear();
    setName(szName);
}


Application::Application(const Application &app) : Node(app)
{
    strName = app.strName;
    strVersion = app.strVersion;
    strDescription = app.strDescription;
    authors = app.authors;
    Imodules = app.Imodules;
    connections = app.connections;  
    Iapplications = app.Iapplications;
    resources = app.resources;
    strXmlFile = app.strXmlFile;
    strPrefix = app.strPrefix;
}


Application::~Application() { }


Node* Application::clone(void)
{
    Application* app = new Application(*this);
    return app; 
}


bool Application::addImodule(ModuleInterface &imod)
{
    Imodules.push_back(imod);
    return true;
}


bool Application::removeImodule(ModuleInterface& imod)
{
    IModuleIterator itr = findImodule(imod);
    if(itr == Imodules.end()) 
        return true;
    Imodules.erase(itr);
    return true;    
}


bool Application::addConnection(Connection &cnn)
{
    connections.push_back(cnn);
    return true;
}


bool Application::removeConnecrion(Connection& cnn)
{
    CnnIterator itr = findConnection(cnn);
    if(itr == connections.end()) 
        return true;
    connections.erase(itr);
    return true;    
    
}

/*
void Application::updateConnectionPrefix(void)
{
    CnnIterator itr;
    for(itr=connections.begin(); itr<connections.end(); itr++) 
    {
        string strPort; 
        if(!((*itr).isExternalFrom()))
        {
            strPort = strPrefix + string((*itr).from()); 
            (*itr).setFrom(strPort.c_str());
        }

        if(!((*itr).isExternalTo()))
        {
            strPort = strPrefix + string((*itr).to()); 
            (*itr).setTo(strPort.c_str());
        }
    }
}
*/

bool Application::addIapplication(ApplicationInterface &iapp)
{
    Iapplications.push_back(iapp);
    return true;
}


bool Application::removeIapplication(ApplicationInterface& iapp)
{
    IApplicationIterator itr = findIapplication(iapp);
    if(itr == Iapplications.end()) 
        return true;
    Iapplications.erase(itr);
    return true;
}

bool Application::addResource(ResYarpPort &res)
{
    resources.push_back(res);
    return true;
}


bool Application::removeResource(ResYarpPort& res)
{
    ResourceIterator itr = findResource(res);
    if(itr == resources.end()) 
        return true;
    resources.erase(itr);
    return true;
}


IModuleIterator Application::findImodule(ModuleInterface& imod) 
{
    IModuleIterator itr;
    for(itr=Imodules.begin(); itr<Imodules.end(); itr++) 
        if ((*itr) == imod)
            return itr;
    return Imodules.end();
}


CnnIterator Application::findConnection(Connection& cnn)
{
    CnnIterator itr;
    for(itr=connections.begin(); itr<connections.end(); itr++) 
        if ((*itr) == cnn)
            return itr;
    return connections.end();   
}

IApplicationIterator Application::findIapplication(ApplicationInterface& iapp) 
{
    IApplicationIterator itr;
    for(itr=Iapplications.begin(); itr<Iapplications.end(); itr++) 
        if ((*itr) == iapp)
            return itr;
    return Iapplications.end();
}

ResourceIterator Application::findResource(ResYarpPort& res) 
{
    ResourceIterator itr;
    for(itr=resources.begin(); itr<resources.end(); itr++) 
        if ((*itr) == res)
            return itr;
    return resources.end();
}



