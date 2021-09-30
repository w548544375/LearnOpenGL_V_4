#ifndef __SCENE3D_H__
#define __SCENE3D_H__
#include "common.h"
#include "Camera3D.h"
#include "Object3D.h"
#include <vector>
class Scene3D : public Object3D
{
public:
    Scene3D();
    void Add(Object3D *);
    void Remove(Object3D *);
    Object3D *Get(unsigned int id);
    std::vector<Object3D *> GetAll();
    virtual void Draw();
    virtual void Tick(float deltaTime);
    virtual void Destroy();
private:
    void init();
    std::vector<Object3D *> objects;
};

#endif
