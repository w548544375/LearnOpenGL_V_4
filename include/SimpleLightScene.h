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
    void registerCallbacks();
    void SetParam();
    unsigned int VAO;
    unsigned int VBO;
    Camera3D *camera;
    unsigned int program;

    float fov = 45.0f;
    float windowWidth;
    float windowHeight;

    glm::vec3 position;

    GLFWwindow *ctx;

    void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
    void ProcessInput(GLFWwindow *window);
    void MouseCallBack(GLFWwindow *window, double x, double y);
    void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
};

#endif