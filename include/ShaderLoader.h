#ifndef __SHADER_LOADER_H__
#define __SHADER_LOADER_H__
#include "common.h"

typedef struct ShaderSource
{
    GLenum typeEnum;
    const char *path;
} SHADER_SOURCE, *PSHADER_SOURCE;

class ShaderLoader
{

public:
    GLuint creatProgram(ShaderSource *shader);

private:
    GLuint createShader(GLenum vertexOrFragType, const char *path);

    GLint program;
};

#endif