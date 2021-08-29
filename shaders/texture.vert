#version 330 core

layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec2 texCoord;
uniform mat4 mvpMat;

out vec2 v_texCoord;

void main()
{
    gl_Position = mvpMat * vec4(v_Position,1.0);
    v_texCoord = texCoord;
}