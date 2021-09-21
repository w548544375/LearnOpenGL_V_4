#ifndef SDL_RENDERCONTEXT_H
#define SDL_RENDERCONTEXT_H
#include "RenderContext.h"

class SDLRenderContext :public RenderContext {
public:
    SDLRenderContext(const char * title,int width,int height);
    ~SDLRenderContext();
    virtual bool hasError() {return errorOccured;};
private:
    SDL_Window * window;
    SDL_GLContext context;

    void ProcessInput();

    void HandleKeyDown(SDL_Event ev);
    void HandleMouseEvent(SDL_Event ev);

    virtual void ContextExchange();


    bool bFirst;
    float lastX;
    float lastY;

    bool bRotate;
};


#endif // SDL_RENDERCONTEXT_H
