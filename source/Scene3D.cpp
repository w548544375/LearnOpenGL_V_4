#include "Scene3D.h"

Scene3D::Scene3D()
{
}

void Scene3D::init()
{
}

void Scene3D::Run()
{
    for (std::vector<Object3D *>::iterator it = objects.begin(); it != objects.end(); it++)
    {
        Object3D *obj = *it;
        glm::mat4 mvp = camera->getProjectionMatrix() * camera->getViewMatrix() * obj->GetModelMatrix();
        obj->draw();
    }
}