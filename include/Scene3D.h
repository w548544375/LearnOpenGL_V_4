#ifndef __SCENE3D_H__
#define __SCENE3D_H__
#include "common.h"
#include "Camera3D.h"
#include "Object3D.h"
#include <vector>
class Scene3D
{
public:
    Scene3D();
    void Run();
    void Add(Object3D *);
    void Remove(Object3D *);
    Object3D *Get(unsigned int id);

private:
    void init();

    Camera3D *camera;
    std::vector<Object3D *> objects;
    float deltaTime;
    float lastFrame;
};

#endif