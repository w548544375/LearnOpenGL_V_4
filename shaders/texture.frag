#version 330 core

in vec2 v_texCoord;

out vec4 fragColor;

uniform sampler2D texture;

void main()
{
    fragColor = texture2D(texture,v_texCoord);
    //fragColor = vec4(1.0f,0.0f,0.0f,1.0f);
}