#include "BasicLights.h"
#include "RenderContext.h"

BasicLights::BasicLights() : Scene3D()
{
    this->init();
}

void BasicLights::init()
{

    // add light
    this->light = new Cube;
    this->light->SetPosition(glm::vec3(1.2f, 1.0f, 2.0f));
    this->light->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
    this->Add(this->light);

    // add cube
    this->cube = new Cube;
    // this->cube->SetRotation(40.0f, glm::vec3(0, 1, 0));
    // this->cube->SetPosition(glm::vec3(-1.0f, 0.0f, 6.0f));
    this->cubeShader = new Shader("../shaders/lights.vert", "../shaders/lights.frag");
    this->cube->SetShader(this->cubeShader);
    this->Add(this->cube);
}

void BasicLights::Tick(float delta)
{
    Scene3D::Tick(delta);
    Camera3D * camera = this->getRenderContext()->GetCtxCamera();
    CAMERA_INFO info = camera->GetCameraInfo();
    glm::vec3 cameraPos = info.cameraPosition;
    this->cubeShader->active();
    this->cubeShader->setVec3f("lightColor",  1.0f, 1.0f, 1.0f);
    this->cubeShader->setVec3f("objectColor", 1.0f, 0.5f, 0.31f);
    glm::vec3 pos = this->light->GetPosition();
    this->cubeShader->setVec3f("lightPos", pos.x, pos.y, pos.z);
    this->cubeShader->setVec3f("viewPos", cameraPos.x, cameraPos.y, cameraPos.z);
    this->cubeShader->setMat4("projection",camera->getProjectionMatrix());
    this->cubeShader->setMat4("view",camera->getViewMatrix());
    this->cubeShader->setMat4("model", cube->GetModelMatrix());
}