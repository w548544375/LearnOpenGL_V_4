#include "Scene.h"

Scene::Scene(GLFWwindow *window)
{
    this->deltaTime = 0.0f;
    this->lastFrame = 0.0f;
    this->ctx = window;
    position = glm::vec3(0.0f);
    this->fov = 45.0f;
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    this->windowWidth = width * 1.0f;
    this->windowHeight = height * 1.0f;
    float aspect = windowWidth / windowHeight;
    this->camera = new Camera3D(fov, aspect, 1.0f, 100.0f);
    this->camera->SetPosition(glm::vec3(0.0f, 1.0f, 5.0f));
    lastX = windowWidth / 2;
    lastY = windowHeight / 2;
    bFirstMove = true;
}

Scene::~Scene()
{
    delete this->camera;
}

void Scene::FrameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    camera->updateProjection(width * 1.0f / height);
}

void Scene::ProcessInput(GLFWwindow *window)
{
    float currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrame;
    lastFrame = currentFrameTime;
    float cameraSpeed = 2.5 * deltaTime;
    CAMERA_INFO info = camera->GetCameraInfo();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glm::vec3 newPos = info.cameraPosition + info.target * cameraSpeed;
        this->camera->SetPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm::vec3 newPos = info.cameraPosition - info.target * cameraSpeed;
        this->camera->SetPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 newPos = info.cameraPosition - glm::normalize(glm::cross(info.target, info.cameraUp)) * cameraSpeed;
        this->camera->SetPosition(newPos);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm::vec3 newPos = info.cameraPosition + glm::normalize(glm::cross(info.target, info.cameraUp)) * cameraSpeed;
        this->camera->SetPosition(newPos);
    }
}

void Scene::MouseCallBack(GLFWwindow *window, double x, double y)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
    {
        if (bFirstMove)
        {
            lastX = windowWidth / 2;
            lastY = windowHeight / 2;
            bFirstMove = false;
        }
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        float xoffset = lastX - x;
        float yoffset = lastY - y;
        lastX = x;
        lastY = y;
        float cameraSensitivity = 0.05;
        this->camera->AddPitchInput(yoffset * cameraSensitivity);
        this->camera->AddYawInput(xoffset * cameraSensitivity);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Scene::ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    CAMERA_INFO info = camera->GetCameraInfo();
    float fov = info.fov - yoffset;
    if (fov < 1.0f)
    {
        fov = 1.0f;
    }
    else if (fov > 89.0f)
    {
        fov = 89.0f;
    }
    this->camera->updateFOV(fov);
}