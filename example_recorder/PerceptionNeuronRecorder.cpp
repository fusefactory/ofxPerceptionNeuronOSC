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

void PerceptionNeuronRecorder::addData(std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> &avatar, int identifier){
    if(needsClear){
        clearData();
    }
    
    uint64_t time = ofGetSystemTimeMillis();
    
    Json::Value val;
    val["timestamp"] = time;
    val["id"] = identifier;
    Json::Value joints;

    for (int i = PerceptionNeuronJointType::Root; i <= PerceptionNeuronJointType::LeftInHandPinky3; i++) {
        PerceptionNeuronJointType type = static_cast<PerceptionNeuronJointType>(i);
        ofVec3f position = avatar.at(type).getPosition();
        ofVec3f rotation = avatar.at(type).getRotation();

        joints[i]["type"] = type;
        
        joints[i]["position"]["x"] = position.x;
        joints[i]["position"]["y"] = position.y;
        joints[i]["position"]["z"] = position.z;
        
        joints[i]["rotation"]["x"] = rotation.x;
        joints[i]["rotation"]["y"] = rotation.y;
        joints[i]["rotation"]["z"] = rotation.z;
    }
    
    val["joints"] = joints;
    values.append(val);
}

void PerceptionNeuronRecorder::threadedFunction() {
    Json::StreamWriterBuilder builder;
    const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    
    while (isThreadRunning()) {
        lock();
        bool e = ends;
        
        cout << "Saved: " << values.size() << endl;
        
        saveToFile(filename, values);
        needsClear = true;
        unlock();
        
        if(e) stopThread();
        
        sleep(1000);
    }
}

void PerceptionNeuronRecorder::saveToFile(std::string filename, Json::Value &root){
    if(root.size() > 0){
        ofFile file;
        if(file.open(filename, ofFile::Append)){
            Json::StreamWriterBuilder builder;
            builder["indentation"] = "";
            std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
            std::ofstream outputFileStream(ofToDataPath(filename), std::ofstream::app);
            writer -> write(root, &outputFileStream);
            outputFileStream.close();
        }else{
            //ERROR
            ofLogError("ofxPerceptionNeuronOSC::PerceptionNeuronRecorder: file can't be saved " + filename);
        }
    }
}

void PerceptionNeuronRecorder::startRecord(std::string filename){
    PerceptionNeuronRecorder::filename = filename;

    clearData();
    startThread();
}

void PerceptionNeuronRecorder::endRecord(){
    ends = true;
    saveToFile(filename, values);
}

void PerceptionNeuronRecorder::clearData(){
    values.clear();
    needsClear = false;
    ends = false;
}
