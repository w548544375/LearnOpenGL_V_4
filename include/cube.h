#ifndef CUBE_H
#define CUBE_H

#include "Object3D.h"
#include "Shader.h"

class Cube : public Object3D
{
public:
    Cube();
    virtual void Draw();
    virtual void Tick(float delta);
    virtual void SetShaderParam(){};
    void SetShader(Shader * newShader){
        if(this->shader!= nullptr)
        {
            delete this->shader;
        }
        this->shader = newShader;
    }
    Shader * GetShader(){
        return this->shader;
    }
private:
    Shader * shader;
    unsigned int vao;
    unsigned int vbo;
};

#endif // CUBE_H
