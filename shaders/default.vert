#version 330 core

layout(location = 0) in vec3 vPosition;

layout(location = 1) in vec2 vCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 v_Coord;

void main() {
    gl_Position = projection * view * model * vec4(vPosition, 1.0);
    v_Coord = vCoord;
}
