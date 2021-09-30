#ifndef LIGHTTEXTURE_H
#define LIGHTTEXTURE_H
#include "Scene3D.h"
#include "cube.h"
class LightTexture :public Scene3D
{
public:
    LightTexture();
    ~LightTexture();
    virtual void Tick(float delta);
    virtual void Draw();
private:
    Cube * light;
    Cube * cube;
    Shader * cubeShader;
    void init();

    unsigned int diffuse;
    unsigned int specular;
    unsigned int emission;
    unsigned int loadTexture(std::string path);
};

#endif // LIGHTTEXTURE_H
