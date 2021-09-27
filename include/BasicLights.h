#ifndef BASICLIGHTS_H
#define BASICLIGHTS_H
#include "Scene3D.h"
#include "cube.h"

class BasicLights : public Scene3D
{
public:
    BasicLights();

    virtual void Tick(float delta);

private:
    void init();
    Cube *light;
    Cube *cube;
    Shader *lightShader;
    Shader *cubeShader;
};

#endif // BASICLIGHTS_H
