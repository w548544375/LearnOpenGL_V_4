#version 330 core

layout (location = 0)in vec3 aPos;
layout (location = 1)in vec2 vCoord;
layout (location = 2)in vec3 aNormal;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 oCoord;
out vec3 oNormal;
out vec3 oFragPos;

void main()
{
    oFragPos = vec3(model * vec4(aPos,1.0));
    oNormal = mat3(transpose(inverse(model))) * aNormal;
    oCoord = vCoord;
    gl_Position = projection * view * vec4(oFragPos,1.0);
}
