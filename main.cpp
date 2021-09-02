// #include "TrangleScene.h"
#include "SimpleLightScene.h"
//export MESA_GL_VERSION_OVERRIDE=3.3
using namespace std;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
Scene *scene = nullptr;
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main(int argc, char *argv[])
{
    if (!glfwInit())
    {
        cerr << "error init glfw" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!gl3wInit())
    {
        cerr << "error init gl3w" << endl;
        return -1;
    }
    GLFWwindow *window = glfwCreateWindow(800, 450, "OpenGL", nullptr, nullptr);

    if (!window)
    {
        cerr << "error create glfw window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
    // tell GLFW to capture our mouse
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    char str[128];
    sprintf(str, "👿 OpenGL %s,GLSL:%s is used by this program.", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    cout << str << endl;
    glViewport(0, 0, 800, 450);
    // Scene *scene = new TrangleScene;
    // scene = new TextureScene;
    scene = new SimpleLightScene(window);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    delete scene;
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // cout << "window resized : (" << width << "," << height << ");" << endl;
    if (scene == nullptr)
        return;
    scene->FrameBufferSizeCallback(window, width, height);
}

void processInput(GLFWwindow *window)
{
    if (scene == nullptr)
        return;
    scene->ProcessInput(window);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (scene == nullptr)
        return;
    scene->MouseCallBack(window, xpos, ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    if (scene == nullptr)
        return;
    scene->ScrollCallback(window, xoffset, yoffset);
}