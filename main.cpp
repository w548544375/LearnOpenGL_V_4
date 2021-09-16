// #include "TrangleScene.h"
#include "SDL.h"
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

const int DEFAULT_WINDOW_WIDHT = 800;
const int DEFAULT_WINDOW_HEIGHT = 450;

int main(int argc, char *argv[])
{
    SDL_Window * window = SDL_CreateWindow("Learn OpenGL",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_CENTERED,DEFAULT_WINDOW_WIDHT,DEFAULT_WINDOW_HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    if(window == nullptr)
    {
        std::cout << "window init failed with " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Renderer * render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(render == nullptr)
    {
        std::cout << "render create failed." << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if(!context)
    {
        std::cout << "SDL create GL context failed." << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

    if(gl3wInit())
    {
        std::cout << "gl3w init failed." << std::endl;
        return -1;
    }

    if(gl3wIsSupported(4,6))
    {
        std::cout << "gl3w not support OpengGL version 4.6" << std::endl;
    }

    char buf[256];
    memset(buf,0,sizeof(buf));
    sprintf(buf,"Using OpengGL %s,Shading Language Version:%s\n",glGetString(GL_VERSION),glGetString(GL_SHADING_LANGUAGE_VERSION));
    std::cout << buf;

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.4f, 0.4f, 0.5f, 1.0f);
    glViewport(0, 0, DEFAULT_WINDOW_WIDHT, DEFAULT_WINDOW_HEIGHT);


    // Scene *scene = new TrangleScene;
    // scene = new TextureScene;
//    scene = new SimpleLightScene(window);
//    while (!glfwWindowShouldClose(window))
//    {
//        processInput(window);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        scene->display();

//        glfwPollEvents();
//    }
//    delete scene;
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
