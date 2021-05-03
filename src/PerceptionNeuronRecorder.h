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
    void addData(std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> &avatar, ofVec3f offset = ofVec3f(0));
    void endRecord();
    inline std::string getFolder(){return folder;}
    inline void setNumberFramePerFile(const int n){numberFramePerFile = n;}
    bool isRecording(){return isThreadRunning();}
    int getFrameCurrentRecord(){return avatars.size(); }
    
protected:
    int identifier;                 //avatar id
    bool needsClear;                //if yes next data clears values
    bool ends;                      //if yes next stop the thread
    int numberFiles;                //number file for current recording
    int numberFramePerFile = 300;   //number of frame for single json file
    std::string folder;
    vector<PerceptionNeuronJointType> jointTypesToSave;
    
    void threadedFunction();
    void saveToFile(std::string filename,  Json::Value &values);
    virtual void addJSONValue(PerceptionNeuronJointType &type, PerceptionNeuronJoint &joint, Json::Value &joints, const int index);
    
    //buffer where store temp data
    vector<std::map<PerceptionNeuronJointType, PerceptionNeuronJoint>> avatars;
    vector<uint64_t> timestamps;
    vector<ofVec3f> offsets;

    int savedIndex;
};

#endif /* PerceptionNeuronRecorder_hpp */
