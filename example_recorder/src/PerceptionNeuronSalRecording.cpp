//
//  PerceptionNeuronSalRecording.cpp
//  example_recorder
//
//  Created by Matteo on 29/04/21.
//

#include "PerceptionNeuronSalRecording.hpp"

void PerceptionNeuronSalRecording::addJSONValue(PerceptionNeuronJointType &type, PerceptionNeuronJoint &joint, Json::Value &joints, const int index){
    
    if(type == Root){
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
    else if(type == RightUpLeg ||
            type == RightLeg ||
            type == RightFoot ||
            type == LeftUpLeg ||
            type == LeftLeg ||
            type == LeftFoot ||
            type == Spine ||
            type == Spine1 ||
            type == Spine2 ||
            type == Spine3 ||
            type == Neck ||
            type == Head ||
            type == RightShoulder ||
            type == RightArm ||
            type == RightForeArm ||
            type == RightHand ||
            type == LeftShoulder ||
            type == LeftArm ||
            type == LeftForeArm ||
            type == LeftHand ){
        
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
}
