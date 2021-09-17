#ifndef SDL_RENDERCONTEXT_H
#define SDL_RENDERCONTEXT_H
#include "RenderContext.h"
#include "SDL.h"
#include "Camera3D.h"

class SDLRenderContext : RenderContext {
public:
    SDLRenderContext(char * title,int width,int height);
    ~SDLRenderContext();
    void SetRenderObj(Object3D * obj){
        this->obj = obj;
    };
    bool hasError() {return errorOccured;};
private:
    SDL_Window * window;
    SDL_GLContext context;
    bool errorOccured = false;
    Camera3D *camera;
    float fov = 45.0f;
    glm::vec3 position;
    bool stop = false;
    void ProcessInput();

    void HandleKeyDown(SDL_Event ev);
    void HandleMouseEvent(SDL_Event ev);

    void Run();

    UINT32 lastFrame;
    float rate;

    Object3D * obj;
};


#endif // SDL_RENDERCONTEXT_H
