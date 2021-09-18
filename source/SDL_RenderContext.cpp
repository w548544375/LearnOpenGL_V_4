#include "SDL_RenderContext.h"

SDLRenderContext::SDLRenderContext(const char * title,int width,int height) : RenderContext(title,width,height)
{
    this->bFirst = true;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

    if(SDL_Init(SDL_INIT_EVERYTHING ) < 0)
    {
        errorOccured = true;
        std::cerr << "Error Init SDL " << SDL_GetError() << std::endl;
        return;
    }
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

    this->context = SDL_GL_CreateContext(window);
    if(!this->context)
    {
        errorOccured = true;
        std::cerr << "SDL create GL context failed." << SDL_GetError() << std::endl;
        return;
    }
    SDL_GL_SetSwapInterval(1);
    if(gl3wInit())
    {
        errorOccured = true;
        std::cerr << "gl3w init failed " << std::endl;
        return;
    }

    if(!gl3wIsSupported(4,6))
    {
        errorOccured = true;
        std::cout << "gl3w not support OpengGL version 4.6" << std::endl;
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
        case SDL_MOUSEBUTTONUP:
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
    if(ev.type == SDL_MOUSEMOTION) {
        //        std::cout << "Motion({x:" << ev.motion.x  << ",y:" << ev.motion.y << "}),RelMotion({x:" << ev.motion.xrel << ",y:" << ev.motion.yrel << "});\n";
        if(bFirst){
            this->lastX = this->Width() / 2.0f;
            this->lastY = this->Height() / 2.0f;
            this->bFirst = false;
        }
        float x = ev.motion.x;
        float y = ev.motion.y;
        this->camera->AddPitchInput(y * this->cameraSensitive);
        this->camera->AddYawInput(x * this->cameraSensitive);
    }
}

void SDLRenderContext::ContextExchange()
{
    SDL_GL_SwapWindow(this->window);
}





SDLRenderContext::~SDLRenderContext()
{
    SDL_DestroyWindow(this->window);
    if(this->obj != nullptr)
    {
        this->obj->Destroy();
        delete this->obj;
    }
}
