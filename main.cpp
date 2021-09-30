// #include "TrangleScene.h"
#include "SDL.h"
#include "SDL_RenderContext.h"
#include "Scene3D.h"
#include "cube.h"
//#include "BasicLights.h"
//#include "LightTexture.h"
#include "LightCasters.h"
#include "LoadModel.h"
//#include "TrangleScene.h"
//export MESA_GL_VERSION_OVERRIDE=3.3
using namespace std;
const int DEFAULT_WINDOW_WIDHT = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;


int main(int argc, char *argv[])
{
    RenderContext * ctx = new SDLRenderContext("OpenGLDemo",DEFAULT_WINDOW_WIDHT,DEFAULT_WINDOW_HEIGHT);
    if(ctx->hasError()){
        std::cerr << "error occured while create context" << std::endl;
        exit(1);
    }
    Scene3D * scene = new LoadModel;
    ctx->SetRenderObj(scene);
//    glm::vec3 cubePositions[] = {
//        glm::vec3( 0.0f,  0.0f,  0.0f),
//        glm::vec3( 2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3( 2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3( 1.3f, -2.0f, -2.5f),
//        glm::vec3( 1.5f,  2.0f, -2.5f),
//        glm::vec3( 1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//    for(int i =0;i < 10 ;i++) {
//        Object3D * obj = new Cube;
//        obj->SetPosition(cubePositions[i]);
//        float angle = 20.0f * i;
//        obj->SetRotation(glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
//        scene->Add(obj);
//    }

    ctx->Run();
    SDL_Quit();
    return 0;
}
