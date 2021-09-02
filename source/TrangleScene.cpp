#include "TrangleScene.h"

TrangleScene::TrangleScene(GLFWwindow *window) : Scene(window)
{
    const float points[] = {
        0.0f,
        0.5f,
        0.0f,
        1.0f,
        0.5f,
        -0.366f,
        0.0f,
        1.0f,
        -0.5f,
        -0.366f,
        0.0f,
        1.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        1.0f,
        0.0f,
        0.0f,
        1.0f,
        1.0f,
    };
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // std::string vertex = "#version 330\nlayout(location = 0) in vec4 a_Position;\nlayout(location = 1) in vec4 a_Color;\nsmooth out vec4 v_Color; \n\n void main() \n{\ngl_Position = a_Position;\nv_Color = a_Color;\n\n}";
    // std::string frag = "#version 330\nsmooth in vec4 v_Color;\nout vec4 outputColor;\n void main() \n{\noutputColor = v_Color;\n}";

    // GLuint vertexShader = this->CreateShader(GL_VERTEX_SHADER, vertex);
    // GLuint fragShader = this->CreateShader(GL_FRAGMENT_SHADER, frag);

    // GLuint program = glCreateProgram();
    // glAttachShader(program, vertexShader);
    // glAttachShader(program, fragShader);

    // glLinkProgram(program);

    // GLint status;
    // glGetProgramiv(program, GL_LINK_STATUS, &status);
    // if (status == GL_FALSE)
    // {
    //     GLint infoLogLength;
    //     glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    //     GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    //     glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
    //     fprintf(stderr, "Linker failure: %s\n", strInfoLog);
    //     delete[] strInfoLog;
    // }

    ShaderLoader loader;
    ShaderSource shaders[] = {{GL_VERTEX_SHADER, "./shaders/trangle.vert"},
                              {GL_FRAGMENT_SHADER, "./shaders/trangle.frag"}};
    GLuint program = loader.creatProgram(shaders);
    glUseProgram(program);
}

TrangleScene::~TrangleScene()
{
}

GLuint TrangleScene::CreateShader(GLenum eShaderType, const std::string &strShaderFile)
{
    GLuint shader = glCreateShader(eShaderType);
    const char *strFileData = strShaderFile.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char *strShaderType = NULL;
        switch (eShaderType)
        {
        case GL_VERTEX_SHADER:
            strShaderType = "vertex";
            break;
        case GL_GEOMETRY_SHADER:
            strShaderType = "geometry";
            break;
        case GL_FRAGMENT_SHADER:
            strShaderType = "fragment";
            break;
        }

        fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
        delete[] strInfoLog;
    }

    return shader;
}

void TrangleScene::display()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)48);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}