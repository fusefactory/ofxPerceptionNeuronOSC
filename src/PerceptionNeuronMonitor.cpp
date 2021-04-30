//
//  PerceptionNeuronMonitor.cpp
//  Dokk
//
//  Created by Paolo Bonacini on 14/12/16.
//
//

#include "PerceptionNeuronMonitor.h"

PerceptionNeuronMonitor::PerceptionNeuronMonitor(PerceptionNeuronReceiver * receiver, float width, float height) {
    PerceptionNeuronMonitor::receiver = receiver;
    
    projection.makeIdentityMatrix();
    projection.makeOrthoMatrix(0, width, height, 0, -1000, 1000);  // vertical flip
    modelview.makeIdentityMatrix();
    modelview.translate(width / 2.0, height /2.0, 0);
    
    fbo.allocate(width, height, GL_RGBA);
    init();
}

void PerceptionNeuronMonitor::draw(float x, float y, float width, float height) {
    update();
    
    fbo.begin();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    render();
    fbo.end();
    
    fbo.draw(x, y, width, height);
}

void PerceptionNeuronMonitor::update() {
    std::vector<ofVec4f> positions;
    std::vector<ofVec4f> colors;
    
    //center from root
    ofVec3f root = receiver->avatar.at(PerceptionNeuronJointType::Root).getPosition();
    
    for (int i = PerceptionNeuronJointType::Root; i <= PerceptionNeuronJointType::LeftInHandPinky3; i++) {
        PerceptionNeuronJointType type = static_cast<PerceptionNeuronJointType>(i);
        ofVec3f position = receiver->avatar.at(type).getPosition() - root;
        positions.push_back(ofVec4f(position.x, position.y, position.z, 1));
        
        colors.push_back(ofVec4f(1, 0, 0, 1));
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ofVec4f) * (PerceptionNeuronJointType::LeftInHandPinky3 + 1), positions.data(), GL_DYNAMIC_COPY);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ofVec4f) * (PerceptionNeuronJointType::LeftInHandPinky3 + 1), colors.data(), GL_DYNAMIC_COPY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PerceptionNeuronMonitor::init() {
    shader.load("shaders/perception_neuron/perception.vert", "shaders/perception_neuron/perception.frag");
    
    glGenBuffers(1, &positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ofVec4f) * (PerceptionNeuronJointType::LeftInHandPinky3 + 1), 0, GL_DYNAMIC_COPY);
    
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ofVec4f) * (PerceptionNeuronJointType::LeftInHandPinky3 + 1), 0, GL_DYNAMIC_COPY);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(ofVec4f), 0);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(ofVec4f), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void PerceptionNeuronMonitor::render() {
    shader.begin();
    
    shader.setUniformMatrix4f("projection", projection);
    shader.setUniformMatrix4f("modelview", modelview);
    shader.setUniform1f("size", 10.0);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, (PerceptionNeuronJointType::LeftInHandPinky3 + 1));
    glBindVertexArray(0);
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_BLEND);
    
    shader.end();
}
