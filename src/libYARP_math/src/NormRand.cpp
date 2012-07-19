// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
* Author: Lorenzo Natale
* Copyright (C) 2010 The RobotCub Consortium
* CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
*
*/ 

#include <yarp/math/NormRand.h>
#include <yarp/math/RandnScalar.h>

using namespace yarp::math;
 
/* should be thread safe, from gsl */
yarp::math::RandnScalar theRandnScalar;

double NormRand::scalar(double u, double sigma)
{
    return theRandnScalar.get(u,sigma);
}

yarp::sig::Vector NormRand::vector(int s, double u, double sigma)
{
    yarp::sig::Vector ret((size_t) s);
    for(int k=0;k<s;k++)
    {
        ret[k]=theRandnScalar.get(u, sigma);
    }

    return ret;
}

yarp::sig::Vector NormRand::vector(const yarp::sig::Vector &u, const yarp::sig::Vector &sigma)
{
    yarp::sig::Vector ret(u.length());
    for(size_t k=0;k<u.length();k++)
    {
        ret[k]=theRandnScalar.get(u[k], sigma[k]);
    }

    return ret;
}

yarp::sig::Matrix NormRand::matrix(int rows, int cols, double u, double sigma)
{
    yarp::sig::Matrix ret(rows,cols);
    for(int r=0;r<rows;r++)
        for(int c=0;c<cols;c++)
        {
            ret[r][c]=theRandnScalar.get(u, sigma);
        }
    return ret;
}
 
void NormRand::init()
{
    theRandnScalar.init();
}
    
void NormRand::init(int seed)
{
    theRandnScalar.init(seed);
}

