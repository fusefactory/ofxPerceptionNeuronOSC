//
//  PerceptionNeuronReceiver.cpp
//  Dokk
//
//  Created by Paolo Bonacini on 25/11/16.
//
//

#include "PerceptionNeuronReceiver.h"

const std::string PERCEPTION_JOINT = "/perception_joint";

PerceptionNeuronReceiver::PerceptionNeuronReceiver(int port, int identifier) {
    PerceptionNeuronReceiver::port = port;
    PerceptionNeuronReceiver::identifier = identifier;

    for (int i = PerceptionNeuronJointType::Root; i <= PerceptionNeuronJointType::LeftInHandPinky3; i++ ) {
        PerceptionNeuronJointType type = static_cast<PerceptionNeuronJointType>(i);
        avatar.insert({ type, PerceptionNeuronJoint(type) });
    }
}

void PerceptionNeuronReceiver::addListener(PerceptionNeuronListener *listener) {
    listeners.push_back(listener);
}

int PerceptionNeuronReceiver::refreshTime() {
    return ofGetElapsedTimeMillis() - lastTime;
}

int PerceptionNeuronReceiver::getIdentifier() {
    return identifier;
}

void PerceptionNeuronReceiver::start() {
    lastTime = ofGetElapsedTimeMillis();
    receiver.setup(port);
    startThread();
}

void PerceptionNeuronReceiver::threadedFunction() {
    while (isThreadRunning()) {
        if (lock()) {
            while (receiver.hasWaitingMessages()) {
                ofxOscMessage message;
                receiver.getNextMessage(message);
                
                if (message.getAddress() == PERCEPTION_JOINT) {
                    if (message.getNumArgs() == 8) {
                        PerceptionNeuronJointType type = static_cast<PerceptionNeuronJointType>(message.getArgAsInt(0));
                        float posX = message.getArgAsFloat(1);
                        float posY = message.getArgAsFloat(2);
                        float posZ = message.getArgAsFloat(3);
                        float rotX = message.getArgAsFloat(4);
                        float rotY = message.getArgAsFloat(5);
                        float rotZ = message.getArgAsFloat(6);
                        float rotW = message.getArgAsFloat(7);

                        PerceptionNeuronJoint &joint = avatar.at(type);
                        joint.setPosition(posX, posY, posZ);
                        joint.setRotation(rotX, rotY, rotZ, rotW);
                        
                        for (PerceptionNeuronListener *listener : listeners) {
                            listener->newJoint(joint);
                        }
                    }
                }
            }
            unlock();
            sleep(10);
        }
    }
}



