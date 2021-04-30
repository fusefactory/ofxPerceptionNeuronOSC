#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    #ifdef _WIN32
        settings.glVersionMajor = 4;
        settings.glVersionMinor = 4;
    #endif
    #ifdef __APPLE__
        settings.glVersionMajor = 3;
        settings.glVersionMinor = 3;
    #endif
    settings.setSize(1000, 700);
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    mainWindow->setWindowTitle("Perception Neuron OSC Reader");

    shared_ptr<ofApp> mainApp(new ofApp);
    ofRunApp(mainWindow, mainApp);          //execute setup

    ofRunMainLoop();
}
