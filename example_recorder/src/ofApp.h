#pragma once

#include "ofMain.h"
#include "ofxPerceptionNeuronOSC.h"
#include "PerceptionNeuronRecorder.h"
#include "PerceptionNeuronSalRecording.hpp"

class ofApp : public ofBaseApp, public PerceptionNeuronListener{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        void newJoint(PerceptionNeuronJoint &joint) override;
        PerceptionNeuronReceiver *perceptionNeuronReceiver;
        PerceptionNeuronMonitor *perceptionNeuronMonitor;
        ofRectangle perceptionNeuronRect;
        std::map<PerceptionNeuronJointType, PerceptionNeuronJoint> *perceptionNeuronAvatar;
        int perceptionTime;
    
    
        PerceptionNeuronRecorder recorder;
        bool saving  = false;
    };
