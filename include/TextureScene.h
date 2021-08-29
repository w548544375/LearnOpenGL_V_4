#ifndef __TEXTURE_SCENE_H__
#define __TEXTURE_SCENE_H__

#include "common.h"
#include "Scene.h"
#include "ShaderLoader.h"

#endif

class TextureScene : public Scene
{
public:
 TextureScene();
 ~TextureScene();
 
 virtual void display();
private:
    void init();
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    unsigned int vertexShader;
    unsigned int fragShader;
    unsigned int program;
    float * points;
    unsigned char * indies;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};