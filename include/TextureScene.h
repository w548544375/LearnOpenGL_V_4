#ifndef __TEXTURE_SCENE_H__
#define __TEXTURE_SCENE_H__

#include "common.h"
#include "Scene.h"
#include "ShaderLoader.h"

#endif

class TextureScene : public Scene
{
public:
    TextureScene();
    ~TextureScene();

    virtual void display();
    void onInput(GLFWwindow *window, float deltaTime);
    void onMouseEvent(GLFWwindow *window, double xpos, double ypos);
    void onScroll(GLFWwindow *window, double xoffset, double yoffset);

private:
    void init();
    void initProgarm();
    void setProgramParam();
    void setTexture();

    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    float fov = 45.0f;
    bool firstMouse = true;
    float yaw = -90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 450.0 / 2.0;

    unsigned int program;
    float *points;
    unsigned int *indies;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};