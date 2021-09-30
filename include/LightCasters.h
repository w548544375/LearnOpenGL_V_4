#ifndef LIGHTTEXTURE_H
#define LIGHTTEXTURE_H
#include "Scene3D.h"
#include "cube.h"
class LightCasters :public Scene3D
{
public:
    LightCasters();
    ~LightCasters();
    virtual void Tick(float delta);
    virtual void Draw();
private:
    Cube * light;
    void init();

    unsigned int diffuse;
    unsigned int specular;
    unsigned int emission;
    unsigned int loadTexture(std::string path);
};

#endif // LIGHTTEXTURE_H
