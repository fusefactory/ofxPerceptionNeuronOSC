#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    perceptionNeuronReceiver = new PerceptionNeuronReceiver(7432);
//    perceptionNeuronReceiver->addListener(this);
//    perceptionNeuronReceiver->start();
    perceptionNeuronMonitor = new PerceptionNeuronMonitor(perceptionNeuronReceiver, ofGetWidth() / 2.0, ofGetHeight() / 2.0);
    perceptionNeuronMonitor->init();
    perceptionTime = ofGetSystemTimeMillis();
    
    cout << "Loading record from files " << endl;
    reader.loadAsync(ofToDataPath("records/c"));
}

//--------------------------------------------------------------
void ofApp::update(){
    if(reader.isRunning()){
        reader.update();
        perceptionNeuronReceiver->avatar = reader.getCurrentAvatar();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    perceptionNeuronRect.set(10, 10, 980, 680);
    int time = ofGetSystemTimeMillis() - perceptionTime;
    if (time > 500) {
        ofFill();
        ofSetColor(255, 0, 0);
    }
    ofSetColor(255, 200);
    ofNoFill();
    ofDrawRectangle(perceptionNeuronRect);   //rect perception neuron
    ofFill();
    ofSetColor(255, 255, 0);
    perceptionNeuronMonitor->draw(perceptionNeuronRect.x, perceptionNeuronRect.y, perceptionNeuronRect.width, perceptionNeuronRect.height);
    ofSetColor(128, 128, 128);
    
    ofDrawBitmapString("Perception Neuron", perceptionNeuronRect.getPosition().x + 5, perceptionNeuronRect.getPosition().y + 15);
    ofDrawBitmapStringHighlight("framerate - " + ofToString(ofGetFrameRate(), 3), 15, 60, ofColor(0, 127), ofColor(255));

    string text = "";
    if(!reader.isReady()){
        text = "Loading";
    }
    else if(reader.isReady() && ! reader.isRunning()){
        text = "Ready";
    }
    else if(reader.isRunning()){
        text = "Running " + ofToString(reader.getFrameNum());
    }
       
    ofDrawBitmapStringHighlight("Status: " + text, 15, 80, ofColor(0, 127), ofColor(255));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='s'){
        if(reader.isReady()) reader.start();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
