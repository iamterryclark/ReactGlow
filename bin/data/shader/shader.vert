
// vertex shader

#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
out vec4 posToFrag;

void main(){
    posToFrag = position;
    gl_Position = modelViewProjectionMatrix * posToFrag;
}
