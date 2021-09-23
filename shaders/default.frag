#version 330 core

in vec2 v_Coord;

uniform sampler2D texture;

out vec4 fragColor;

void main(){
//    fragColor = texture2D(texture,v_Coord);
    fragColor = vec4(1.0f,1.0f,1.0f,1.0f);
}
