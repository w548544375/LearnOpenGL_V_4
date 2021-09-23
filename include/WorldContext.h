#ifndef WORLDCONTEXT_H
#define WORLDCONTEXT_H
class RenderContext;

class World{

public:

    World(World &other) = delete;
    void operator=(const World &) = delete;

    static World *GetWorld();
    void SetWorldRenderContext(RenderContext * contex);
    RenderContext * GetRenderContext();
protected:
    World();
    RenderContext * ctx;
    static World * inst;
};

#endif // WORLDCONTEXT_H
