#ifndef __SCENE3D_H__
#define __SCENE3D_H__
#include "common.h"

class Scene3D
{
public:
    void Run();

private:
    void init();

    float deltaTime;
    float lastFrame;
};

#endif