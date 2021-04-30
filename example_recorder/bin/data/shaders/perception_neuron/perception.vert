#version 330

uniform mat4 projection;
uniform mat4 modelview;
uniform float size;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 vertColor;

void main()
{
    gl_Position = projection * modelview * position;
   	gl_PointSize = size;
   	
   	vertColor = color;
}