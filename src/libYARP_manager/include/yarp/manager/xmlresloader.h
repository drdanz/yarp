/*
 *  Yarp Modules Manager
 *  Copyright: (C) 2011 Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Ali Paikan <ali.paikan@iit.it>
 *
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#ifndef YARP_MANAGER_XMLRESLOADER
#define YARP_MANAGER_XMLRESLOADER

#include <yarp/manager/ymm-types.h>
#include <yarp/manager/resource.h>
#include <yarp/manager/primresource.h>
#include <yarp/manager/manifestloader.h>

namespace yarp {
namespace manager {
class TextParser;

/**
 * Class XmlResLoader
 */
class XmlResLoader : public ResourceLoader
{
public:
    XmlResLoader(const char* szFileName);
    XmlResLoader(const char* szPath, const char* szResName);
    virtual ~XmlResLoader();
    bool init(void) YARP_OVERRIDE;
    void reset(void) YARP_OVERRIDE;
    void fini(void) YARP_OVERRIDE;
    GenericResource* getNextResource(void) YARP_OVERRIDE;

protected:

private:
    std::string strName;
    std::string strPath;
    std::string strFileName;
    std::vector<std::string> fileNames;
    TextParser*    parser;
    ComputerContainer computers;
    Computer dummyComputer;
    bool parsXml(const char* szFile);
};

} // namespace yarp
} // namespace manager


#endif // __YARP_MANAGER_XMLRESLOADER__
