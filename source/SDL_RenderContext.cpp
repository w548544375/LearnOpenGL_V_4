#include "SDL_RenderContext.h"

SDLRenderContext::SDLRenderContext(const char * title,int width,int height) : RenderContext(title,width,height)
{
    this->bRotate = false;
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

    SDL_Renderer * render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    float cameraSpeed = 2.5f * this->rate;
    CAMERA_INFO info = camera->GetCameraInfo();
    switch(ev.key.keysym.sym)
    {
    case SDLK_w:
    {
        this->camera->SetPosition(info.front * cameraSpeed );
        break;
    }
    case SDLK_q:
    {
        this->camera->SetPosition(info.up * cameraSpeed);
        break;
    }
    case SDLK_e:
    {
        this->camera->SetPosition(-info.up * cameraSpeed);
        break;
    }
    case SDLK_s:
    {
        this->camera->SetPosition(-info.front * cameraSpeed);
        break;
    }
    case SDLK_a:
    {
        this->camera->SetPosition(-info.right * cameraSpeed);
        break;
    }
    case SDLK_d:
    {
        this->camera->SetPosition(info.right * cameraSpeed);
        break;
    }
    }
}

void SDLRenderContext::HandleMouseEvent(SDL_Event ev)
{
    if(ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_RIGHT){
        SDL_SetRelativeMouseMode(SDL_TRUE);
//        SDL_SetWindowGrab(this->window,SDL_TRUE);
        bRotate = true;
    }
    if(ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_RIGHT) {
        SDL_SetRelativeMouseMode(SDL_FALSE);
//        SDL_SetWindowGrab(this->window,SDL_FALSE);
        bRotate = false;
    }
    if(ev.type == SDL_MOUSEMOTION && bRotate) {
        float x = ev.motion.xrel;
        float y = ev.motion.yrel;
//                std::cout << "Motion({x:" << x  << ",y:" << y << "}),RelMotion({x:" << lastX << ",y:" << lastY << "});\n";
//                std::flush(std::cout);
        this->camera->AddPitchInput(y *  0.0001);
        this->camera->AddYawInput(x * 0.0001);
    }

    if(ev.type == SDL_MOUSEWHEEL)
    {
        CAMERA_INFO info = this->camera->GetCameraInfo();
        float fov = info.fov - ev.wheel.y * 108.0f * this->rate;
        if(fov > 89.9f)
            fov = 89.9f;
        if(fov < 0.1f)
            fov = 0.1f;
        this->camera->updateFOV(fov);
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
