#ifndef __TRANGLE_SCENE__
#define __TRANGLE_SCENE__
#include "common.h"
#include "Scene.h"
#include "ShaderLoader.h"

class TrangleScene : public Scene
{

public:
    TrangleScene(GLFWwindow *window);
    ~TrangleScene();
    virtual void display();
    GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);

private:
    GLuint VBO;
};

#endif