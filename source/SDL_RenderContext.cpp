#include "SDL_RenderContext.h"

SDLRenderContext::SDLRenderContext(char * title,int width,int height) : RenderContext(title,width,height)
{
    this->window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,contextWidth,contextHeight,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    if(!this->window)
    {
        errorOccured = true;
        std::cerr << "error create sdl window " << SDL_GetError() << std::endl;
        return;
    }
    SDL_Renderer * render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(render == nullptr)
    {
        errorOccured = true;
        std::cerr << "render create failed " << SDL_GetError() << std::endl;
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

    if(gl3wInit())
    {
        errorOccured = true;
        std::cerr << "gl3w init failed." << std::endl;
        return;
    }

    if(!gl3wIsSupported(4,5))
    {
        errorOccured = true;
        std::cout << "gl3w not support OpengGL version 4.5" << std::endl;
    }

    this->context = SDL_GL_CreateContext(window);
    if(!this->context)
    {
        errorOccured = true;
        std::cerr << "SDL create GL context failed." << SDL_GetError() << std::endl;
        return;
    }

    char buf[256];
    memset(buf,0,sizeof(buf));
    sprintf(buf,"Using OpengGL %s,Shading Language Version:%s\n",glGetString(GL_VERSION),glGetString(GL_SHADING_LANGUAGE_VERSION));
    std::cout << buf;
}

void SDLRenderContext::ProcessInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0)
    {
        switch(event.type)
        {
        case SDL_QUIT:
            stop = true;
            break;
        case SDL_KEYDOWN:
            HandleKeyDown(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEWHEEL:
        case SDL_MOUSEMOTION:
            HandleMouseEvent(event);
            break;
        }
    }
}

void SDLRenderContext::HandleKeyDown(SDL_Event ev)
{
    float cameraSpeed = 2.5 * this->rate;
    CAMERA_INFO info = camera->GetCameraInfo();
    switch(ev.key.keysym.sym)
    {
    case SDLK_w:
    {
        glm::vec3 add = info.cameraPosition + info.target * cameraSpeed;
        this->camera->SetPosition(add);
        break;
    }
    case SDLK_s:
    {
        glm::vec3 minus = info.cameraPosition - info.target * cameraSpeed;
        this->camera->SetPosition(minus);
        break;
    }
    case SDLK_a:
    {
        glm::vec3 moveL = info.cameraPosition - glm::normalize(glm::cross(info.target, info.cameraUp)) * cameraSpeed;
        this->camera->SetPosition(moveL);
        break;
    }
    case SDLK_d:
    {
        glm::vec3 moveR = info.cameraPosition + glm::normalize(glm::cross(info.target, info.cameraUp)) * cameraSpeed;
        this->camera->SetPosition(moveR);
        break;
    }
    }
}

void SDLRenderContext::HandleMouseEvent(SDL_Event ev)
{

}

void SDLRenderContext::Run()
{
    if(nullptr != this->obj) {
        this->obj->draw();
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
        SDL_GL_SwapWindow(this->window);
    }
}





SDLRenderContext::~SDLRenderContext()
{

}
