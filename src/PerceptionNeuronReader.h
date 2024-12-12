//
//  PerceptionNeuronReader.hpp
//  example_recorder
//
//  Created by Matteo on 30/04/21.
//

#ifndef PerceptionNeuronReader_hpp
#define PerceptionNeuronReader_hpp

#include <stdio.h>
#include "json.h"
#include <map>
#include <vector>
#include "PerceptionNeuronJointType.h"
#include "PerceptionNeuronJoint.h"
#include "PerceptionNeuronReaderData.h"

class PerceptionNeuronReader : public ofThread{
    
public:
    PerceptionNeuronReader();
    
    bool load(std::string folder);          //load all files from a folder
    void loadAsync(std::string folder);     //load in a separate thread all files from folder
    bool isReady();                         //all files are loaded and data is ready in memory
    void update(int time);                          //function to call every update
    void start();                           //start running
    bool isRunning();
    int getFrameNum();
    std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> getCurrentAvatar();
    
protected:
    void threadedFunction();
    bool loadFile(std::string filename);
    void goToNextData();
    
    std::string folder;
    vector<PerceptionNeuronReaderData> percepionNeuronReaderData;
    PerceptionNeuronReaderData *currentPerceptionNeuronReaderData;

    bool ready = false;
    bool running = false;
    
    int currentIndex = -1;

    uint64_t start_t;
    uint64_t end_t;
    
    uint64_t pnTime;
    uint64_t currentTime;
    
    //time
    uint64_t diffNextMillis;          //time in millis to next value

};

#endif /* PerceptionNeuronReader_hpp */
