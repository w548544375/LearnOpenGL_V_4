#version 330 core

layout(location = 0) in vec3 vPosition;

layout(location = 1) in vec2 vCoord;

uniform mat4 mvpMat;

out vec2 v_Coord;

void main() {
    gl_Position = mvpMat * vec4(vPosition, 1.0);
    v_Coord = vCoord;
}