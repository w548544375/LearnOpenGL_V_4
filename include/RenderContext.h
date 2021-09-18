#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H
#include "common.h"
#include "Camera3D.h"

class RenderContext {
public:
    RenderContext(const char * title,int width,int height);
    //    virtual ~RenderContext() = 0;
    void SetRenderObj(Object3D * obj){
        obj->SetRenderContext(this);
        this->obj = obj;
    };
    int Width() const {return contextWidth;};
    int Height() const {return contextHeight;};
    void Run();

    virtual bool hasError(){return false;};
    virtual void ProcessInput(){};
    virtual void ContextExchange(){};
protected:
    int contextWidth;
    int contextHeight;

    bool errorOccured = false;
    float fov = 45.0f;
    glm::vec3 position;
    bool stop = false;

    float cameraSensitive;
    Camera3D * camera;
    Object3D * obj = nullptr;

    UINT32 lastFrame;
    float rate;
    friend class Object3D;
};




#endif // RENDERCONTEXT_H
