#ifndef __SHADER_H__
#define __SHADER_H__
#include "common.h"
class Shader
{
public:
    Shader(std::string vertexPath, std::string fragPath);
    ~Shader();
    void active();

    void setInt(std::string name, int value);

    void setFloat(std::string name, float value);

    void setBool(std::string name, bool value);

    void setVec3f(std::string name, float x, float y, float z);

    void setVec4f(std::string name, float x, float y, float z, float w);

    void setMat4(std::string name, glm::mat4 mat);

protected:
    unsigned int program;

    unsigned int vertexShader;
    unsigned int fragShader;

    std::string loadSource(std::string source) const;
    unsigned int createShader(GLenum shaderType, const char *sourceBytes);

    void linkProgram();
};

#endif
