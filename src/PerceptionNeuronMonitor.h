//
//  PerceptionNeuronMonitor.h
//  Dokk
//
//  Created by Paolo Bonacini on 14/12/16.
//
//

#ifndef PerceptionNeuronMonitor_h
#define PerceptionNeuronMonitor_h

#include <stdio.h>
#include "Renderer.h"
#include "PerceptionNeuronReceiver.h"

class PerceptionNeuronMonitor : public Renderer {
    
public:
    PerceptionNeuronMonitor(PerceptionNeuronReceiver * receiver, float width, float height);
    void init() override;
    void render() override;
    void draw(float x, float y, float width, float height);
    
private:
    PerceptionNeuronReceiver * receiver;
    ofFbo fbo;
    ofShader shader;
    GLuint positionVBO, colorVBO;
    void update();
};

#endif /* PerceptionNeuronMonitor_h */
