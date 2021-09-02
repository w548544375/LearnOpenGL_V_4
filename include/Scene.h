#ifndef __SCENE_H_
#define __SCENE_H_
#include "common.h"
#include "Camera3D.h"
class Scene
{
public:
    virtual void display() = 0;

    Scene(GLFWwindow *window);
    ~Scene();
    void FrameBufferSizeCallback(GLFWwindow *window, int width, int height);
    void ProcessInput(GLFWwindow *window);
    void MouseCallBack(GLFWwindow *window, double x, double y);
    void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
    void Run();

protected:
    Camera3D *camera;
    float fov = 45.0f;
    glm::vec3 position;
    float windowWidth;
    float windowHeight;
    GLFWwindow *ctx;
    float deltaTime;
    float lastFrame;

    float lastX;
    float lastY;
    bool bFirstMove;
};

#endif