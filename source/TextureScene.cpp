#include "TextureScene.h"

TextureScene::TextureScene()
{
}

void TextureScene::init()
{
    this->points = new float[24]{
        0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,
         0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,
    };
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(this->points),this->points,GL_STATIC_DRAW);

    
}

TextureScene::~TextureScene()
{
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragShader);
    glDeleteProgram(this->program);
    delete this->points;
}

void TextureScene::display()
{
}