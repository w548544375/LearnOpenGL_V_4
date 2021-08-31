
#include "ShaderLoader.h"

GLuint ShaderLoader::createShader(GLenum vertexOrFragType, const char *path)
{
    GLint shader = glCreateShader(vertexOrFragType);
    std::ifstream infile(path);
    if (!infile.is_open())
    {
        std::cout << "file " << path << " not found!" << std::endl;
        return shader;
    }
    std::stringstream sstream;
    std::string str;
    sstream << infile.rdbuf();
    str = sstream.str();
    infile.close();
    const char *shaderSource = str.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    // 获取编译结果
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infolength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infolength);
        GLchar *infoStr = new GLchar[infolength + 1];
        glGetShaderInfoLog(shader, infolength, nullptr, infoStr);
        std::string type;
        switch (vertexOrFragType)
        {
        case GL_VERTEX_SHADER:
            type.append("vertex");
            break;
        case GL_FRAGMENT_SHADER:
            type.append("fragment");
            break;
        case GL_GEOMETRY_SHADER:
            type.append("geometry");
            break;
        default:
            break;
        }
        fprintf(stderr, "failed to compile %s shader(%s):%s\r\n", type.c_str(), path, infoStr);
        delete[] infoStr;
    }
    return shader;
}

GLuint ShaderLoader::creatProgram(Shader *shaders)
{
    if (shaders == nullptr)
    {
        return -1;
    }
    GLuint program = glCreateProgram();
    struct Shader *shader = shaders;
    while (shader != nullptr && shader->typeEnum != GL_NONE)
    {
        GLuint createdShader = this->createShader(shader->typeEnum, shader->path);
        glAttachShader(program, createdShader);
        shader++;
    }
    glLinkProgram(program);
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

    return program;
}

// string get_file_string2()
// {
//     ifstream inFile;
//     inFile.open("path_to_file"); //open the input file

//     stringstream strStream;
//     strStream << inFile.rdbuf(); //read the file
//     return strStream.str();      //str holds the content of the file
// }