#ifndef __SCENE3D_H__
#define __SCENE3D_H__
#include "common.h"

class Scene3D
{
public:
    virtual void Tick(float delta) = 0;
    void Run();

private:
    void init();

    float deltaTime;
    float lastFrame;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraPos;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

#endif