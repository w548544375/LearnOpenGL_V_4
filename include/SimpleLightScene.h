#ifndef __SIMPLE_LIGHT_SCENE_H__
#define __SIMPLE_LIGHT_SCENE_H__
#include "common.h"
#include "Scene.h"
#include "Camera3D.h"

class SimpleLightScene : public Scene
{
private:
    /* data */
public:
    SimpleLightScene(GLFWwindow *window);
    ~SimpleLightScene();
    virtual void display();

private:
    int SetTexture(std::string name, GLenum textureIdx, std::string path, int textureLocation);
    void init();
    void SetParam();
    unsigned int VAO;
    unsigned int VBO;

    unsigned int program;
};

#endif