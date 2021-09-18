// #include "TrangleScene.h"
#include "SDL.h"
#include "SDL_RenderContext.h"
#include "Scene3D.h"
//export MESA_GL_VERSION_OVERRIDE=3.3
using namespace std;
const int DEFAULT_WINDOW_WIDHT = 800;
const int DEFAULT_WINDOW_HEIGHT = 450;

void processInput();
int main(int argc, char *argv[])
{
    RenderContext * ctx = new SDLRenderContext("OpenGLDemo",DEFAULT_WINDOW_WIDHT,DEFAULT_WINDOW_HEIGHT);
    if(ctx->hasError()){
        std::cerr << "error occured while create context" << std::endl;
        exit(1);
    }
    Scene3D * scene = new Scene3D;
    ctx->SetRenderObj(scene);
    ctx->Run();
    SDL_Quit();
    return 0;
}
