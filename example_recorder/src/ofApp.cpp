#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    
    perceptionNeuronReceiver = new PerceptionNeuronReceiver(7432);
    perceptionNeuronReceiver->addListener(this);
    perceptionNeuronReceiver->start();
    perceptionNeuronMonitor = new PerceptionNeuronMonitor(perceptionNeuronReceiver, ofGetWidth() / 2.0, ofGetHeight() / 2.0);
    perceptionNeuronMonitor->init();
    perceptionTime = ofGetSystemTimeMillis();    
}

//--------------------------------------------------------------
void ofApp::update(){
    if(saving)  recorder.addData(perceptionNeuronReceiver->avatar);
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
    ofDrawBitmapStringHighlight("framerate - " + ofToString(ofGetFrameRate(), 3), 10, 60, ofColor(0, 127), ofColor(255));
}

void ofApp::newJoint(PerceptionNeuronJoint & joint) {
    perceptionTime = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a'){
        cout << "Start of recording " << endl;
        saving = true;
        recorder.startRecord(ofToString(ofGetSystemTimeMillis()));
    }
    if(key=='s'){
        cout << "End of recording. Saved to " << recorder.getFolder() << endl;

        recorder.endRecord();
        saving = false;
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
