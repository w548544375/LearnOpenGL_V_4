#ifndef SIMPLECUBESCENE_H
#define SIMPLECUBESCENE_H
#include "common.h"
#include "Object3D.h"
#include "Shader.h"
class SimpleCubeScene :public Object3D
{
private:
    unsigned int VAO;
    unsigned int VBO;

    unsigned int texture0;
    Shader * shader;
public:
    SimpleCubeScene();
    ~SimpleCubeScene();
    virtual void Tick(float delta);
};


#endif // SIMPLECUBESCENE_H
