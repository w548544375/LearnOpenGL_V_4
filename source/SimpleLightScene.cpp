#include "SimpleLightScene.h"
#include "ShaderLoader.h"

SimpleLightScene::SimpleLightScene(GLFWwindow *window) : Scene(window)
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1); // coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    glBindVertexArray(0);

    this->init();
}

void SimpleLightScene::init()
{
    ShaderSource shaders[] = {{GL_VERTEX_SHADER, "./shaders/simple_light.vert"},
                              {GL_FRAGMENT_SHADER, "./shaders/simple_light.frag"},
                              {GL_NONE, ""}};
    ShaderLoader loader;
    this->program = loader.creatProgram(shaders);
    this->SetTexture("texture", GL_TEXTURE0, "./assets/TexturesCom_MetalFloorsPainted0012_1_seamless_S.jpg", 0);
}

int SimpleLightScene::SetTexture(std::string name, GLenum textureIdx, std::string path, int textureLocation)
{
    // 设置texture参数
    unsigned int tex;
    glGenTextures(1, &tex);
    glActiveTexture(textureIdx);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &height, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "cant find texture: " << path << std::endl;
        return -1;
    }
    // 设置texture
    int samplerLocation = glGetUniformLocation(this->program, name.c_str());
    glUniform1d(samplerLocation, textureLocation);
    return tex;
}

SimpleLightScene::~SimpleLightScene()
{
}

void SimpleLightScene::SetParam()
{
    unsigned int matLocation = glGetUniformLocation(this->program, "mvpMat");
    glm::mat4 translate = glm::mat4(1.0f);
    translate = glm::translate(translate, position);
    // translate = glm::scale(translate, glm::vec3(3.0f, 3.0f, 3.0f));
    glm::mat4 mvp = this->camera->getProjectionMatrix() * this->camera->getViewMatrix() * translate;
    glUniformMatrix4fv(matLocation, 1, false, glm::value_ptr(mvp));
}

void SimpleLightScene::display()
{
    glUseProgram(this->program);
    glBindVertexArray(this->VAO);
    this->SetParam();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);
    glBindVertexArray(0);
}
