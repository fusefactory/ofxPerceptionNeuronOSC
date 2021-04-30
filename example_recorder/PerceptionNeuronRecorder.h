//
//  PerceptionNeuronRecorder.hpp
//  example_recorder
//
//  Created by Matteo on 29/04/21.
//

#ifndef PerceptionNeuronRecorder_hpp
#define PerceptionNeuronRecorder_hpp

#include <stdio.h>
#include <map>
#include "PerceptionNeuronJointType.h"
#include "PerceptionNeuronJoint.h"
#include "json.h"

class PerceptionNeuronRecorder : public ofThread{
public:
    PerceptionNeuronRecorder();
    void startRecord(std::string filename);
    void addData(std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> &avatar, int identifier = 0);
    void endRecord();
    
private:
    bool needsClear;
    bool ends;
    std::string filename;
    Json::Value values;
    
    void threadedFunction();
    void saveToFile(std::string filename,  Json::Value &values);
    void clearData();
};

#endif /* PerceptionNeuronRecorder_hpp */
