//
//  PerceptionNeuronSalRecording.hpp
//  example_recorder
//
//  Created by Matteo on 29/04/21.
//

#ifndef PerceptionNeuronSalRecording_hpp
#define PerceptionNeuronSalRecording_hpp

#include <stdio.h>
#include "PerceptionNeuronRecorder.h"

class PerceptionNeuronSalRecording : public PerceptionNeuronRecorder{
protected:
    void addJSONValue(PerceptionNeuronJointType &type, PerceptionNeuronJoint &joint, Json::Value &joints, const int index) override;
};

#endif /* PerceptionNeuronSalRecording_hpp */
