//
//  PerceptionNeuronJoint.cpp
//  Dokk
//
//  Created by Paolo Bonacini on 25/11/16.
//
//

#include "PerceptionNeuronJoint.h"

PerceptionNeuronJoint::PerceptionNeuronJoint(PerceptionNeuronJointType type) {
    PerceptionNeuronJoint::type = type;
}

void PerceptionNeuronJoint::setPosition(float posX, float posY, float posZ) {
    position.set(posX, posY, posZ);
}

void PerceptionNeuronJoint::setRotation(float rotX, float rotY, float rotZ, float rotW) {
    rotation.set(rotX, rotY, rotZ, rotW);
}

PerceptionNeuronJointType PerceptionNeuronJoint::getType() {
    return type;
}

ofVec3f PerceptionNeuronJoint::getPosition() {
    return position;
}

ofVec4f PerceptionNeuronJoint::getRotation() {
    return rotation;
}
