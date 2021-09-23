#include "WorldContext.h"

World* World::inst = nullptr;

World::World()
{

}


World * World::GetWorld()
{
    if(nullptr == inst)
    {
        inst = new World();
    }
    return inst;
}

void World::SetWorldRenderContext(RenderContext *contex)
{
    this->ctx = contex;
}

RenderContext * World::GetRenderContext()
{
    return this->ctx;
}
