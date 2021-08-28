#include "TrangleScene.h"
//export MESA_GL_VERSION_OVERRIDE=3.3
using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main(int argc, char *argv[])
{
    if (!glfwInit())
    {
        cerr << "error init glfw" << endl;
        return -1;
    }
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

    glClearColor(0.4f, 0.4f, 0.5f, 1.0f);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    char str[128];
    sprintf(str, "👿 OpenGL %s,GLSL:%s is used by this program.", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    cout << str << endl;

    glViewport(0, 0, 800, 450);

    Scene *scene = new TrangleScene;
    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);
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
    glViewport(0, 0, width, height);
}