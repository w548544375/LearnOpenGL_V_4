#include "Scene3D.h"

Scene3D::Scene3D()
{
    this->init();
}

void Scene3D::init()
{
    glEnable(GL_DEPTH_TEST);
//    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
}

void Scene3D::Draw()
{
    std::vector<Object3D*>::iterator it = this->objects.begin();
    while (it != this->objects.end()) {
        Object3D * obj = *it;
        obj->Draw();
        it++;
    }
}

void Scene3D::Destroy()
{
    std::vector<Object3D*>::iterator it = this->objects.begin();
    while(it != this->objects.end())
    {
        Object3D * obj = *it;
        obj->Destroy();
        it++;
    }
    this->objects.clear();
}

void Scene3D::Tick(float deltaTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::vector<Object3D*>::iterator it = this->objects.begin();
    while(it != this->objects.end())
    {
       Object3D * obj = *it;
       obj->Tick(deltaTime);
       it++;
    }
}

void Scene3D::Add(Object3D *obj)
{
    obj->SetRenderContext(this->getRenderContext());
    this->objects.push_back(obj);
}

void Scene3D::Remove(Object3D *obj)
{
    for(std::vector<Object3D*>::iterator it = this->objects.begin();it != this->objects.end();it++)
    {
        if(obj == *it)
        {
            this->objects.erase(it);
            break;
        }
    }
}

std::vector<Object3D*> Scene3D::GetAll()
{
    return this->objects;
}


Object3D * Scene3D::Get(unsigned int id)
{
    return this->objects.at(id);
}

