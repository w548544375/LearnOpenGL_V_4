#version 330 core

layout(location = 0) in vec3 vPosition;

layout(location = 1) in vec2 vCoord;

layout(location = 2) in vec3 aNormal;

uniform mat4 mvpMat;

uniform mat4 model;

out vec2 v_Coord;

out vec3 oNormal;

out vec3 FragPos;


void main() {
    FragPos = vec3(model * vec4(vPosition,1.0));
    oNormal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = mvpMat * vec4(FragPos, 1.0);
    v_Coord = vCoord;
    //  oNormal = aNormal;
}
