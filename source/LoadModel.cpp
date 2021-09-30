#include "LoadModel.h"

ModelScene::ModelScene(const char * path) : Object3D()
{
        this->model= new Model(path);
        this->shader = new Shader("../shaders/model_loading.vert","../shaders/model_loading.frag");
}


ModelScene::~ModelScene()
{
    delete this->model;
    delete this->shader;
}

void ModelScene::Draw()
{
    Object3D::Draw();
    this->model->Draw(*this->shader);
}


LoadModel::LoadModel() : Scene3D()
{
    modelScene = new ModelScene("../assets/erika_archer.fbx");
    this->Add(modelScene);
}

void LoadModel::Draw()
{
    Scene3D::Draw();
}
