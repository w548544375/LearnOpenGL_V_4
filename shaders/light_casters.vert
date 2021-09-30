#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vCoord;
layout(location = 2) in vec3 vNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 oCoord;
out vec3 oNormal;
out vec3 FragPos;


void main()
{
    FragPos = vec3(model * vec4(vPosition,1.0));
    oNormal = mat3(transpose(inverse(model))) * vNormal;
    oCoord = vCoord;
    gl_Position = projection * view * model * vec4(vPosition,1.0);
}
