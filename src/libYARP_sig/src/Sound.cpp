// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <yarp/sig/Sound.h>
#include <yarp/sig/Image.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/PortablePair.h>
#include <yarp/os/Log.h>

using namespace yarp::sig;
using namespace yarp::os;

#define HELPER(x) (*((FlexImage*)(x)))

Sound::Sound(int bytesPerSample) {
    init(bytesPerSample);
    frequency = 0;
}

Sound::Sound(const Sound& alt) : yarp::os::Portable() {
    init(alt.getBytesPerSample());
    FlexImage& img1 = HELPER(implementation);
    FlexImage& img2 = HELPER(alt.implementation);
    img1.copy(img2);
    frequency = alt.frequency;
    synchronize();
}

const Sound& Sound::operator = (const Sound& alt) {
    YARP_ASSERT(getBytesPerSample()==alt.getBytesPerSample());
    FlexImage& img1 = HELPER(implementation);
    FlexImage& img2 = HELPER(alt.implementation);
    img1.copy(img2);
    frequency = alt.frequency;
    synchronize();
    return *this;
}

void Sound::synchronize() {
    FlexImage& img = HELPER(implementation);
    samples = img.width();
    channels = img.height();
}

void Sound::init(int bytesPerSample) {
    implementation = new FlexImage();
    YARP_ASSERT(implementation!=NULL);

    YARP_ASSERT(bytesPerSample==2); // that's all thats implemented right now
    HELPER(implementation).setPixelSize(sizeof(PixelInt));
    HELPER(implementation).setPixelCode(VOCAB_PIXEL_INT);

    samples = 0;
    channels = 0;
    this->bytesPerSample = bytesPerSample;    
}

Sound::~Sound() {
    if (implementation!=NULL) {
        delete &HELPER(implementation);
        implementation = NULL;
    }
}

void Sound::resize(int samples, int channels) {
    FlexImage& img = HELPER(implementation);
    img.resize(samples,channels);
    synchronize();
}

int Sound::get(int location, int channel) const {
    FlexImage& img = HELPER(implementation);
    unsigned char *addr = img.getPixelAddress(location,channel);
    if (bytesPerSample==2) {
        return *((NetInt32 *)addr);
    }
    YARP_LOG_INFO("sound only implemented for 16 bit samples");
    return 0;
}

void Sound::set(int value, int location, int channel) {
    FlexImage& img = HELPER(implementation);
    unsigned char *addr = img.getPixelAddress(location,channel);
    if (bytesPerSample==2) {
        *((NetInt32 *)addr) = value;
        return;
    }
    YARP_LOG_INFO("sound only implemented for 16 bit samples");
}

int Sound::getFrequency() const {
    return frequency;
}

void Sound::setFrequency(int freq) {
    this->frequency = freq;
}

bool Sound::read(ConnectionReader& connection) {
    // lousy format - fix soon!
    FlexImage& img = HELPER(implementation);
    Bottle bot;
    bool ok = PortablePair<FlexImage,Bottle>::readPair(connection,img,bot);
    frequency = bot.get(0).asInt();
    synchronize();
    return ok;
}


bool Sound::write(ConnectionWriter& connection) {
    // lousy format - fix soon!
    FlexImage& img = HELPER(implementation);
    Bottle bot;
    bot.addInt(frequency);
    return PortablePair<FlexImage,Bottle>::writePair(connection,img,bot);
}

unsigned char *Sound::getRawData() const {
    FlexImage& img = HELPER(implementation);
    return img.getRawImage();
}

int Sound::getRawDataSize() const {
    FlexImage& img = HELPER(implementation);
    return img.getRawImageSize();
}


