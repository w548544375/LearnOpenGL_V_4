#include "TextureScene.h"

TextureScene::TextureScene(GLFWwindow *window) : Scene(window)
{
    this->init();
    this->initProgarm();
    this->setTexture();
}

void TextureScene::init()
{
    cameraPos = glm::vec3(0.0f, 3.0f, 4.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -5.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    model = glm::mat4(1.0);

    this->points = new float[24]{
        0.5f, -0.5f, 0.5f,   // 0
        -0.5f, -0.5f, 0.5f,  // 1
        -0.5f, 0.5f, 0.5f,   // 2
        0.5f, 0.5f, 0.5f,    // 3
        0.5f, -0.5f, -0.5f,  // 4
        -0.5f, -0.5f, -0.5f, // 5
        -0.5f, 0.5f, -0.5f,  // 6
        0.5f, 0.5f, -0.5f    // 7
    };

    this->indies = new unsigned int[36]{
        0, 3, 2,
        0, 2, 1, // front
        0, 7, 3,
        0, 4, 7, // right
        1, 2, 6,
        1, 6, 5, // left
        2, 3, 7,
        2, 7, 6, // top
        0, 5, 1,
        0, 4, 5, // bottom
        4, 6, 5,
        4, 7, 6, // back
    };

    float coords[] = {
        1.0f, 0.0f, // 0
        0.0f, 0.0f, //1
        0.0f, 1.0f, //2
        1.0f, 1.0f, //3
        1.0f, 0.0f, //4
        1.0f, 0.0f, //5
        1.0f, 1.0f, //6
        0.0f, 0.0f  //7
    };

    unsigned int coordsVBO;

    glGenVertexArrays(1, &VAO);
    glCreateBuffers(1, &VBO);
    glCreateBuffers(1, &EBO);
    glGenBuffers(1, &coordsVBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, this->points, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 36, this->indies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, coordsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextureScene::initProgarm()
{
    ShaderLoader loader;
    Shader shaders[] = {{GL_VERTEX_SHADER, "./shaders/texture.vert"},
                        {GL_FRAGMENT_SHADER, "./shaders/texture.frag"},
                        {GL_NONE, ""}};
    this->program = loader.creatProgram(shaders);
    glUseProgram(program);
}

void TextureScene::setTexture()
{
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("./assets/little_dingdang.jpg", &width, &height, &channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    int loc = glGetUniformLocation(this->program, "texture");
    glUniform1d(loc, 0);
}

void TextureScene::setProgramParam()
{
    view = glm::lookAt(cameraPos, cameraFront, cameraUp);
    projection = glm::perspective(glm::radians(fov), 800.0f / 450.0f, 0.1f, 100.0f);
    glm::mat4 mvp = projection * view * model;
    int mvpUniform = glGetUniformLocation(this->program, "mvpMat");
    glUniformMatrix4fv(mvpUniform, 1, false, glm::value_ptr(mvp));
}

TextureScene::~TextureScene()
{
    glDeleteProgram(this->program);
    delete this->points;
}

void TextureScene::display()
{

    glUseProgram(this->program);
    this->setProgramParam();
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void TextureScene::onInput(GLFWwindow *window, float delta)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    float cameraSpeed = 2.5 * delta;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void TextureScene::onMouseEvent(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void TextureScene::onScroll(GLFWwindow *window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 0.1f)
        fov = 0.1f;
    if (fov > 70.0f)
        fov = 70.0f;
}