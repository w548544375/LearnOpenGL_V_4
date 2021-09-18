#include "RenderContext.h"

RenderContext::RenderContext(const char * title,int width,int height)
{
    contextHeight = height;
    contextWidth = width;
    this->cameraSensitive = 0.05;
    this->position = glm::vec3(0.0f,2.0f,-5.0f);
    this->camera = new Camera3D(fov,contextWidth/contextHeight,1.0f,1000.0f);
    this->camera->SetPosition(this->position);
}


void RenderContext::Run()
{
    if(nullptr != this->obj)
    {
        this->obj->Draw();
    }
    while (!stop) {
        Uint32 endTick = SDL_GetTicks();
        this->rate = (endTick - lastFrame) / 1000.0f;
        lastFrame = endTick;
        // display scene;
        this->ProcessInput();
        if(nullptr != this->obj)
        {
            this->obj->Tick(this->rate);
        }
       this->ContextExchange();
    }
}
