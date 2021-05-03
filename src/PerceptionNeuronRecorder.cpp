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

void PerceptionNeuronRecorder::addData(std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> &avatar, ofVec3f offset){
    avatars.push_back(avatar);
    offsets.push_back(offset);
    timestamps.push_back(ofGetSystemTimeMillis());
}

void PerceptionNeuronRecorder::addJSONValue(PerceptionNeuronJointType &type, PerceptionNeuronJoint &joint, Json::Value &joints, const int index){
    ofVec3f position = joint.getPosition();
    ofVec4f rotation = joint.getRotation();

    joints[index]["type"] = type;
    
    joints[index]["position"]["x"] = position.x;
    joints[index]["position"]["y"] = position.y;
    joints[index]["position"]["z"] = position.z;
    
    joints[index]["rotation"]["x"] = rotation.x;
    joints[index]["rotation"]["y"] = rotation.y;
    joints[index]["rotation"]["z"] = rotation.z;
    joints[index]["rotation"]["w"] = rotation.w;
}

void PerceptionNeuronRecorder::threadedFunction() {
    Json::StreamWriterBuilder builder;
    const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    
    while (isThreadRunning()) {
        bool e = ends;
        
        const int avatarSize = avatars.size() - 2; //ignore last data
        const int startIndex = savedIndex;
        const int size = avatarSize - startIndex;
        
        if(size > numberFramePerFile || e){
            //updated
            savedIndex = avatarSize;
            
            Json::Value root;
            for(int i = startIndex; i < avatarSize; i++){
                uint64_t time = timestamps[i];
                ofVec3f& offset = offsets[i];
                std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> &avatar = avatars.at(i);
                
                Json::Value val;
                val["timestamp"] = time;
                Json::Value joints;
                
                for (int j = PerceptionNeuronJointType::Root; j <= PerceptionNeuronJointType::LeftInHandPinky3; j++) {
                    PerceptionNeuronJointType type = static_cast<PerceptionNeuronJointType>(j);
                    if ( avatar.find(type) == avatar.end() ) {
                        // not found
                        ofLogWarning() << "ofxPerceptionNeuronOSC::PerceptionNeuronRecorder not found type " << type << " at index: " << i;
                    } else {
                        // found
                        PerceptionNeuronJoint &joint = avatar.at(type);
                        ofVec3f p = joint.getPosition() + offset;
                        joint.setPosition(p.x, p.y, p.z);
                        addJSONValue(type, joint, joints, joints.size());
                    }
                }
                
                val["joints"] = joints;
                root.append(val);
            }
            
            std::ostringstream oss;
            oss << setw(6) << setfill('0') << (numberFiles +1);
            string s = oss.str();
            std::string path = ofToDataPath(folder + "/pn_" + s + ".json");
            saveToFile(path, root);
            numberFiles ++;
        }
            
        if(e) {
            //clear current vector temp
            avatars.clear();
            timestamps.clear();
            
            ofLogVerbose() << "ofxPerceptionNeuronOSC::PerceptionNeuronRecorder cleared data stop thread ";

            stopThread();
        }
        else sleep(10);
    }
}

void PerceptionNeuronRecorder::saveToFile(std::string filename, Json::Value &root){
    if(root.size() > 0){
        Json::StreamWriterBuilder builder;
        builder["indentation"] = "";
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        std::ofstream outputFileStream(filename, std::ofstream::out);
        writer -> write(root, &outputFileStream);
        outputFileStream.close();
        
        ofLogVerbose() << "ofxPerceptionNeuronOSC::PerceptionNeuronRecorder saved " << root.size() << " frames.";
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
    savedIndex = 0;
    startThread();
}

void PerceptionNeuronRecorder::endRecord(){
    ends = true;
}
