#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    perceptionNeuronReceiver = new PerceptionNeuronReceiver(7432);
    perceptionNeuronReceiver->addListener(this);
    perceptionNeuronReceiver->start();
    perceptionNeuronMonitor = new PerceptionNeuronMonitor(perceptionNeuronReceiver, ofGetWidth() / 2.0, ofGetHeight() / 2.0);
    perceptionNeuronMonitor->init();
    perceptionTime = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update(){

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
}

void ofApp::newJoint(PerceptionNeuronJoint & joint) {
    perceptionTime = ofGetSystemTimeMillis();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
