//
//  PerceptionNeuronJoint.h
//  Dokk
//
//  Created by Paolo Bonacini on 25/11/16.
//
//

#ifndef PerceptionNeuronJoint_h
#define PerceptionNeuronJoint_h

#include <stdio.h>
#include <string>
#include "ofMain.h"
#include "PerceptionNeuronJointType.h"

class PerceptionNeuronJoint {
    
public:
    PerceptionNeuronJoint(PerceptionNeuronJointType type);
    void setPosition(float posX, float posY, float posZ);
    void setRotation(float rotX, float rotY, float rotZ, float rotW);
    PerceptionNeuronJointType getType();
    ofVec3f getPosition();
    ofVec4f getRotation();
    
private:
    PerceptionNeuronJointType type;
    ofVec3f position;
    ofVec4f rotation;   //quaternion components
};

#endif /* PerceptionNeuronJoint_h */
