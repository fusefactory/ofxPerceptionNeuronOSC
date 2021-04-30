//
//  PerceptionNeuronListener.h
//  Dokk
//
//  Created by Paolo Bonacini on 25/11/16.
//
//

#ifndef PerceptionNeuronListener_h
#define PerceptionNeuronListener_h

#include "PerceptionNeuronJoint.h"

class PerceptionNeuronListener {
    
public:
    virtual void newJoint(PerceptionNeuronJoint & joint) { };
};

#endif /* PerceptionNeuronListener_h */
