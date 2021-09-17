#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H
#include "common.h"

class RenderContext {
public:
    RenderContext(char * title,int width,int height){
        contextHeight = height;
        contextWidth = width;
    };
//    virtual ~RenderContext() = 0;

    int Width() const {return contextWidth;};
    int Height() const {return contextHeight;};

protected:
   int contextWidth;
   int contextHeight;
};




#endif // RENDERCONTEXT_H
