//
//  PerceptionNeuronReceiver.h
//  Dokk
//
//  Created by Paolo Bonacini on 25/11/16.
//
//

#ifndef PerceptionNeuronReceiver_h
#define PerceptionNeuronReceiver_h

#include <stdio.h>
#include <map>
#include <vector>
#include "PerceptionNeuronListener.h"
#include "PerceptionNeuronJoint.h"
#include "ofxOscReceiver.h"

class PerceptionNeuronReceiver : public ofThread {
    
public:
    PerceptionNeuronReceiver(int port, int identifier = 0);
    void addListener(PerceptionNeuronListener *listener);
    int refreshTime();
    int getIdentifier();
    void start();
    std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> avatar;
    
private:
    int port;
    int identifier = 0;
    ofxOscReceiver receiver;
    std::vector<PerceptionNeuronListener*> listeners;
    void threadedFunction();
    int lastTime;
};

#endif /* PerceptionNeuronReceiver_h */
