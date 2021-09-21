#ifndef __TRANGLE_SCENE__
#define __TRANGLE_SCENE__
#include "common.h"
#include "Object3D.h"
#include "ShaderLoader.h"

class TrangleScene : public Object3D
{

public:
    TrangleScene();
    ~TrangleScene();
    virtual void Tick(float delta);
    GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);

private:
    GLuint VBO;
};

#endif
