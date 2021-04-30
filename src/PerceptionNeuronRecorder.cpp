//
//  PerceptionNeuronRecorder.cpp
//  example_recorder
//
//  Created by Matteo on 29/04/21.
//

#include "PerceptionNeuronRecorder.h"
#include "ofUtils.h"
#include <iostream>
#include <fstream>

PerceptionNeuronRecorder::PerceptionNeuronRecorder(){

}

void PerceptionNeuronRecorder::addData(std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> &avatar){
    if(needsClear){
        clearData();
    }
    
    uint64_t time = ofGetSystemTimeMillis();
    
    Json::Value val;
    val["timestamp"] = time;
    Json::Value joints;

    for (int i = PerceptionNeuronJointType::Root; i <= PerceptionNeuronJointType::LeftInHandPinky3; i++) {
        PerceptionNeuronJointType type = static_cast<PerceptionNeuronJointType>(i);
        PerceptionNeuronJoint &joint = avatar.at(type);
        addJSONValue(type, joint, joints, i);
    }
    
    val["joints"] = joints;
    values.append(val);
}

void PerceptionNeuronRecorder::addJSONValue(PerceptionNeuronJointType &type, PerceptionNeuronJoint &joint, Json::Value &joints, const int index){
    ofVec3f position = joint.getPosition();
    ofVec3f rotation = joint.getRotation();

    joints[index]["type"] = type;
    
    joints[index]["position"]["x"] = position.x;
    joints[index]["position"]["y"] = position.y;
    joints[index]["position"]["z"] = position.z;
    
    joints[index]["rotation"]["x"] = rotation.x;
    joints[index]["rotation"]["y"] = rotation.y;
    joints[index]["rotation"]["z"] = rotation.z;
}

void PerceptionNeuronRecorder::threadedFunction() {
    Json::StreamWriterBuilder builder;
    const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    
    while (isThreadRunning()) {
        lock();
        bool e = ends;
        
        cout << "Saved: " << values.size() << endl;
        
        std::string path = ofToDataPath(folder + "/pn_" + ofToString(numberFiles) + ".json");
        saveToFile(path, values);
        numberFiles ++;
        
        needsClear = true;
        unlock();
        
        if(e) stopThread();
        
        sleep(10000);
    }
}

void PerceptionNeuronRecorder::saveToFile(std::string filename, Json::Value &root){
    if(root.size() > 0){
        Json::StreamWriterBuilder builder;
        builder["indentation"] = "";
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        std::ofstream outputFileStream(filename, std::ofstream::app);
        writer -> write(root, &outputFileStream);
        outputFileStream.close();
    }
}

void PerceptionNeuronRecorder::startRecord(std::string folder, int identifier){
    PerceptionNeuronRecorder::folder = folder;
    PerceptionNeuronRecorder::identifier = identifier;
    
    ofDirectory dir(folder);
    if(!dir.exists()){
        dir.create(true);
    }

    numberFiles = 0;
    clearData();
    startThread();
}

void PerceptionNeuronRecorder::endRecord(){
    ends = true;
}

void PerceptionNeuronRecorder::clearData(){
    values.clear();
    needsClear = false;
    ends = false;
}
