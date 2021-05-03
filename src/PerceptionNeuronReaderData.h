//
//  PerceptionNeuronReaderData.hpp
//  example_reader
//
//  Created by Matteo on 30/04/21.
//

#ifndef PerceptionNeuronReaderData_hpp
#define PerceptionNeuronReaderData_hpp

#include <stdio.h>
#include <map>
#include "PerceptionNeuronJointType.h"
#include "PerceptionNeuronJoint.h"

class PerceptionNeuronReaderData{
public:
    std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> avatar;
    uint64_t timeMillis; //ofGetSystemTimeMillis()
};

#endif /* PerceptionNeuronReaderData_hpp */
