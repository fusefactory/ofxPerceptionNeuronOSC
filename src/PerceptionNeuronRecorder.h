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
    void startRecord(std::string folder, int identifier = 0);
    void addData(std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> &avatar);
    void endRecord();
    inline std::string getFolder(){return folder;}
    
protected:
    int identifier;
    bool needsClear;            //if yes next data clears values
    bool ends;
    int numberFiles;
    std::string folder;
    Json::Value values;
    vector<PerceptionNeuronJointType> jointTypesToSave;
    
    void threadedFunction();
    void saveToFile(std::string filename,  Json::Value &values);
    void clearData();
    virtual void addJSONValue(PerceptionNeuronJointType &type, PerceptionNeuronJoint &joint, Json::Value &joints, const int index);
};

#endif /* PerceptionNeuronRecorder_hpp */
