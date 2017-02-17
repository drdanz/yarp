/*
 * Copyright (C) 2015  iCub Facility, Istituto Italiano di Tecnologia
 * Author: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
 *
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#ifndef YARP_OVRHEADSET_TEXTUREBUFFER_H
#define YARP_OVRHEADSET_TEXTUREBUFFER_H

#include <GL/glew.h>
#include <OVR_Math.h>
#include <yarp/os/Mutex.h>


class TextureBuffer
{
public:
#if OVR_PRODUCT_VERSION == 0 && OVR_MAJOR_VERSION <= 5
    TextureBuffer(int w, int h, int eye);
#else
    TextureBuffer(int w, int h, int eye, ovrHmd hmd);
#endif

    ~TextureBuffer();

    void resize(int w = 0, int h = 0);
    void update();

#if OVR_PRODUCT_VERSION == 0 && OVR_MAJOR_VERSION <= 5
#else
    ovrHmd hmd;
    ovrSwapTextureSet* textureSet;
#endif

    unsigned int width;
    unsigned int height;
    unsigned int padding;
    unsigned int rowSize;
    unsigned int bufferSize;

    ovrPosef eyePose;

    GLuint texId;
    GLuint pboIds[2];
    unsigned int pboIndex;
    unsigned int pboNextIndex;

    GLubyte* ptr;
    bool dataReady;
    yarp::os::Mutex mutex;

    unsigned int missingFrames;

    unsigned int imageWidth;
    unsigned int imageHeight;

private:
    void createTextureAndBuffers();
    void deleteTextureAndBuffers();
    int eye;
};

#endif // YARP_OVRHEADSET_TEXTUREBUFFER_H
