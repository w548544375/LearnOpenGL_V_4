#include "RenderContext.h"

RenderContext::RenderContext(const char * title,int width,int height)
{
    contextHeight = height;
    contextWidth = width;
    this->cameraSensitive = 0.05;
    this->camera = new Camera3D(45.0f,contextWidth * 1.0f/contextHeight,0.1f,100.0f);
//    this->camera->updateProjection(fov);
}


void RenderContext::Run()
{
    while (!stop) {
        Uint32 endTick = SDL_GetTicks();
        this->rate = (endTick - lastFrame) / 1000.0f;
        lastFrame = endTick;
        // display scene;
        this->ProcessInput();
        if(nullptr != this->obj)
        {
            this->obj->Tick(this->rate);
            this->obj->Draw();
        }
       this->ContextExchange();
    }
}
