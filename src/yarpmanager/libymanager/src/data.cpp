/*
 *  Yarp Modules Manager
 *  Copyright: 2011 (C) Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Ali Paikan <ali.paikan@iit.it>
 * 
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include "data.h"

/**
 * Class InputData
 */
InputData::InputData(void) : Node(INPUTD) 
{
    bRequired = false;
    bWithPriority = false;
}

InputData::InputData(const char* szName) : Node(INPUTD) 
{
    bRequired = false;
    bWithPriority = false;
    setName(szName);
}

InputData::InputData(const InputData &input) : Node(input)
{
    strName = input.strName;
    strPort = input.strPort; 
    carrier = input.carrier;
    bWithPriority = input.bWithPriority;    
    bRequired = input.bRequired;
    strDescription = input.strDescription;
}


InputData::~InputData() { }


Node* InputData::clone(void)
{
    InputData* input = new InputData(*this);
    return input; 
}




/**
 * Class OutputData
 */
OutputData::OutputData(void) : Node(OUTPUTD) {}


OutputData::OutputData(const char* szName) : Node(OUTPUTD) 
{
    setName(szName);
}


OutputData::OutputData(const OutputData &output) : Node(output)
{
    strName = output.strName;
    strPort = output.strPort; 
    carrier = output.carrier;
    strDescription = output.strDescription;
}


OutputData::~OutputData() { }


Node* OutputData::clone(void)
{
    OutputData* output = new OutputData(*this);
    return output; 
}

