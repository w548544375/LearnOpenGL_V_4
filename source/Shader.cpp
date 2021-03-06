#include "Shader.h"

Shader::Shader(std::string vertexSource, std::string fragSource)
{
    std::string vertexbytes = this->loadSource(vertexSource);
    std::string fragbytes = this->loadSource(fragSource);
    this->vertexShader = this->createShader(GL_VERTEX_SHADER, vertexbytes.c_str());
    this->fragShader = this->createShader(GL_FRAGMENT_SHADER, fragbytes.c_str());
    this->linkProgram();
}

Shader::~Shader()
{
}

std::string Shader::loadSource(std::string path) const
{
    std::ifstream str(path);
    if (!str.is_open())
    {
        return nullptr;
    }
    std::stringstream ssr;
    ssr << str.rdbuf();
    std::string sourceString = ssr.str();
    return sourceString;
}

unsigned int Shader::createShader(GLenum type, const char *data)
{
    unsigned int shaderId = glCreateShader(type);
    if (nullptr == data)
    {
        return shaderId;
    }
    glShaderSource(shaderId, 1, &data, nullptr);
    glCompileShader(shaderId);
    int status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infolength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infolength);
        GLchar *infoStr = new GLchar[infolength + 1];
        glGetShaderInfoLog(shaderId, infolength, nullptr, infoStr);
        std::string shaderTypeStr;
        switch (type)
        {
        case GL_VERTEX_SHADER:
            shaderTypeStr.append("vertex");
            break;
        case GL_FRAGMENT_SHADER:
            shaderTypeStr.append("fragment");
            break;
        case GL_GEOMETRY_SHADER:
            shaderTypeStr.append("geometry");
            break;
        default:
            break;
        }
        fprintf(stderr, "failed to compile %s shader:%s\r\n", shaderTypeStr.c_str(), infoStr);
        delete[] infoStr;
    }
    return shaderId;
}

void Shader::linkProgram()
{
    this->program = glCreateProgram();
    glAttachShader(this->program, vertexShader);
    glAttachShader(this->program, fragShader);
    glLinkProgram(this->program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
        GLchar *infoStr = new GLchar[infoLength + 1];
        glGetProgramInfoLog(program, infoLength, nullptr, infoStr);
        fprintf(stderr, "link program %s\r\n", infoStr);
        delete[] infoStr;
    }
}

void Shader::active()
{
    glUseProgram(this->program);
}

void Shader::setInt(std::string name, int value)
{
    int location = glGetUniformLocation(this->program, name.c_str());
    glUniform1i(location, value);
}

void Shader::setVec3f(std::string name, float x, float y, float z)
{
    int location = glGetUniformLocation(this->program, name.c_str());
    glUniform3f(location,x,y,z);
}

void Shader::setVec4f(std::string name, float x, float y, float z, float w)
{
    int location = glGetUniformLocation(this->program, name.c_str());
    glUniform4f(location,x,y,z,w);
}

void Shader::setMat4(std::string name, glm::mat4 mat)
{
    int location = glGetUniformLocation(this->program, name.c_str());
    glUniformMatrix4fv(location, 1, false, glm::value_ptr(mat));
}

void Shader::setFloat(std::string name, float value)
{
    int location = glGetUniformLocation(this->program, name.c_str());
    glUniform1f(location, value);
}

void Shader::setBool(std::string name, bool value)
{
    int location = glGetUniformLocation(this->program, name.c_str());
    glUniform1i(location, value);
}
