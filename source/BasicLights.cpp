#include "BasicLights.h"

BasicLights::BasicLights() : Scene3D()
{
    this->init();
}


void BasicLights::init()
{

    // add light
    this->light = new Cube;
    this->light->SetScale(glm::vec3(0.4f,0.4f,0.4f));
    this->light->SetPosition(glm::vec3(-6.0f,4.0f,2.0f));
    this->Add(this->light);

    // add lights
    this->cube = new Cube;
    this->cube->SetScale(glm::vec3(1.5f,1.5f,1.5f));
    this->cube->SetRotation(40.0f,glm::vec3(0,1,0));
    this->cube->SetPosition(glm::vec3(1.0f,0.0f,-1.0f));
    this->cubeShader = new Shader("./shaders/lights.vert","./shaders/lights.frag");
    this->cube->SetShader(this->cubeShader);
    this->Add(this->cube);
    this->cubeShader->active();
    this->cubeShader->setVec3f("lightColor",1.0f,1.0f,1.0f);
    this->cubeShader->setVec3f("objectColor",1.0f, 0.5f, 0.31f);
    this->cubeShader->setMat4("model",cube->GetModelMatrix());
    glm::vec3 pos = this->light->GetPosition();
    this->cubeShader->setVec3f("lightPos",pos.x,pos.y,pos.z);
}


