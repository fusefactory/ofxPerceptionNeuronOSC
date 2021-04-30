//
//  Renderer.h
//  TestSketch
//
//  Created by Paolo Bonacini on 07/07/16.
//
//

#pragma once
#include "ofMain.h"
#include <stdio.h>

class Renderer {
    
public:
    virtual void init() {};
    virtual void render() {};
    ofMatrix4x4 projection;
    ofMatrix4x4 modelview;
    
protected:
    GLuint vao;
    ofShader shader;
};
