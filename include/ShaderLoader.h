#ifndef __SHADER_LOADER_H__
#define __SHADER_LOADER_H__
#include "common.h"

typedef struct Shader
{
    GLenum typeEnum;
    const char *path;
} SHADER, *PSHADER;

class ShaderLoader
{

public:
    GLuint creatProgram(Shader *shader);

private:
    GLuint createShader(GLenum vertexOrFragType, const char *path);

    GLint program;
};

#endif