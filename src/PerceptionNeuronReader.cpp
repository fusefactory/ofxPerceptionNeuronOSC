//
//  PerceptionNeuronReader.cpp
//  example_recorder
//
//  Created by Matteo on 30/04/21.
//

#include "PerceptionNeuronReader.h"
#include "ofMain.h"

bool endsWithCaseInsensitive(std::string mainStr, std::string toMatch)
{
    auto it = toMatch.begin();
    return mainStr.size() >= toMatch.size() &&
            std::all_of(std::next(mainStr.begin(),mainStr.size() - toMatch.size()), mainStr.end(), [&it](const char & c){
                return ::tolower(c) == ::tolower(*(it++))  ;
    } );
}

PerceptionNeuronReader::PerceptionNeuronReader(){
    
}

std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> PerceptionNeuronReader::getCurrentAvatar() {
    if (ready) {
        return currentPerceptionNeuronReaderData->avatar;
    } else {
        // Return a default value or throw an exception
        return std::map<PerceptionNeuronJointType, PerceptionNeuronJoint>(); // Return an empty map
    }
}


bool PerceptionNeuronReader::isReady(){return ready;}
bool PerceptionNeuronReader::isRunning(){return running;}
int PerceptionNeuronReader::getFrameNum(){return currentIndex;}

void PerceptionNeuronReader::start(){
    running = true;
//    goToNextData();
    currentIndex = 0;
    update(0);
}

bool PerceptionNeuronReader::load(std::string folder){
    ofDirectory dir(folder);
    if(!dir.exists()){
        ofLogError() << "ofxPerceptionNeuronOSC::PerceptionNeuronReader folder not found: " <<  folder;
        return false;
    }
    
    ready = false;
    running = false;
    dir = dir.getSorted();

    //go through and print out all the paths
    for(ofFile file : dir.getFiles()){
        if(endsWithCaseInsensitive(file.getFileName(), ".json")){
            loadFile(file.getAbsolutePath());
            
//            cout << "percepionNeuronReaderData.size(): " << percepionNeuronReaderData.size() << endl;
        }
    }
    
    start_t = percepionNeuronReaderData.at(0).timeMillis;
    end_t = percepionNeuronReaderData.at(percepionNeuronReaderData.size()-1).timeMillis;
    pnTime = 0;
    currentTime = 0;
    
    ready = true;
    
    return ready;
}

void PerceptionNeuronReader::loadAsync(std::string folder){
    PerceptionNeuronReader::folder = folder;
    startThread();
}

void PerceptionNeuronReader::threadedFunction(){
    while (isThreadRunning()) {
        load(folder);
        
        stopThread();
    }
}

bool PerceptionNeuronReader::loadFile(std::string filename){
    Json::Value root;

    std::ifstream file(filename);
    file >> root;
    
    for(int i = 0; i < root.size(); i++){
       // cout << root[i] << endl;
        PerceptionNeuronReaderData data;
        data.timeMillis = root[i]["timestamp"].asInt64();
        
        Json::Value &joints = root[i]["joints"];
        for(int j = 0; j < joints.size(); j ++){
            Json::Value &jointValue = joints[j];
            PerceptionNeuronJointType type = static_cast<PerceptionNeuronJointType>(jointValue["type"].asInt());
            PerceptionNeuronJoint joint(type);
            
            if(! jointValue["position"].empty()){
                joint.setPosition(jointValue["position"]["x"].asFloat(),
                                  jointValue["position"]["y"].asFloat(),
                                  jointValue["position"]["z"].asFloat());
            }
            if(! jointValue["rotation"].empty()){
                joint.setRotation(jointValue["rotation"]["x"].asFloat(),
                                  jointValue["rotation"]["y"].asFloat(),
                                  jointValue["rotation"]["z"].asFloat(),
                                  jointValue["rotation"]["w"].asFloat());
            }
            
            data.avatar.insert({ type, joint });
        }
        
        percepionNeuronReaderData.push_back(data);
    }
    
    vector<string> splitString = ofSplitString(filename, "/");
    string name = "";
    if(splitString.size() > 0) name = splitString.at(splitString.size()-1);
    ofLogVerbose() << "ofxPerceptionNeuronOSC::PerceptionNeuronDataReader::loadFile LOADED filename:" << name;
    
    return false;
}

void PerceptionNeuronReader::update(int time){
    currentTime = time;
    
    if (loop) {
        if (currentTime < start_t){
            currentTime += start_t;
        }
        else if (currentTime > end_t) {
            currentTime = currentTime % (end_t - start_t) + start_t;
        }
    }
    
    if(ready && running){
        if (currentTime > start_t && currentTime < end_t){
            goToNextData();
            uint64_t ellapsedTimeMillis = ofGetElapsedTimeMillis();
            if(ofGetElapsedTimeMillis() - currentPerceptionNeuronReaderData->timeMillis > diffNextMillis){
                goToNextData();
            }
        }
        else{
            currentPerceptionNeuronReaderData = &percepionNeuronReaderData.at(0);
        }
    }
}

void PerceptionNeuronReader::goToNextData(){
    
    // Seek time if the distance is too high
    int distance = glm::abs(currentTime-pnTime);
    if (distance > 1000){
        int bias = 100;
        if (bias >= percepionNeuronReaderData.size()){
            bias = 1;
        }
        
        int testTime = pnTime;
        int prevTestTime = 0;
        int testIndex = bias;
        if (pnTime > currentTime){
            testTime = start_t;
        }
        
        while (testTime <= currentTime && testIndex < percepionNeuronReaderData.size()) {
            prevTestTime = testTime;
            currentPerceptionNeuronReaderData = &percepionNeuronReaderData.at(testIndex);
            testTime = currentPerceptionNeuronReaderData->timeMillis;
            
            if (testTime > currentTime){
                currentIndex = testIndex-bias;
                pnTime = prevTestTime;
//                cout << "Seek time: " << ofToString(currentTime) << " | " << ofToString(pnTime) << endl;
                break;
            } else{
                testIndex += bias;
//                testIndex ++;
            }
        }
    }
    
    while (currentTime > pnTime && currentIndex < percepionNeuronReaderData.size()-1){
        currentIndex++;
        
        currentPerceptionNeuronReaderData = &percepionNeuronReaderData.at(currentIndex);
        pnTime = currentPerceptionNeuronReaderData->timeMillis;
    }
    
    
//    currentIndex++;
//    
//    //loop
//    if(currentIndex == percepionNeuronReaderData.size()) {
//        ofLogWarning() << "ofxPerceptionNeuronOSC::PerceptionNeuronDataReader the record is ended > restart." << endl;
//        currentIndex = 0;
//    }
//    
//    currentPerceptionNeuronReaderData = &percepionNeuronReaderData.at(currentIndex);
//
//    if(currentIndex < percepionNeuronReaderData.size()-1){
//        PerceptionNeuronReaderData &nextData = percepionNeuronReaderData.at(currentIndex+1);
//        uint64_t nextDataTime = nextData.timeMillis;
//        
//        diffNextMillis = nextDataTime - currentPerceptionNeuronReaderData->timeMillis;
//    }
}


void PerceptionNeuronReader::setLoop(bool _l){
    loop = _l;
}

