#ifndef LOADMODEL_H
#define LOADMODEL_H
#include "Scene3D.h"
#include "Model.h"
class ModelScene :public Object3D
{
public:
    virtual void Draw();
    ModelScene(const char * path);
    ~ModelScene();
private:
    Model * model;
    Shader * shader;
};



class LoadModel :public Scene3D
{
public:
    virtual void Draw();
    LoadModel();
private:
    ModelScene * modelScene;
};



#endif // LOADMODEL_H
