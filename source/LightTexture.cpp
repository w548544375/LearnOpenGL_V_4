#include "LightTexture.h"
#include "RenderContext.h"

LightTexture::LightTexture() : Scene3D()
{
    this->cubeShader = nullptr;
    this->init();
}

LightTexture::~LightTexture()
{

}

void LightTexture::Tick(float delta)
{
    Scene3D::Tick(delta);
    if(this->cubeShader){
        this->cubeShader->active();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,this->diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,this->specular);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D,this->emission);

        glm::vec3 lightPos = this->light->GetPosition();

        this->cubeShader->setVec3f("light.position",lightPos.x,lightPos.y,lightPos.z);
        glm::vec3 cameraPos = this->getRenderContext()->GetCtxCamera()->GetCameraInfo().cameraPosition;
        this->cubeShader->setVec3f("viewPos",cameraPos.x,cameraPos.y,cameraPos.z);
        this->cubeShader->setFloat("material.shininess",128.0f);
        this->cubeShader->setVec3f("light.ambient", 0.2f, 0.2f, 0.2f);
        this->cubeShader->setVec3f("light.diffuse", 1.0f, 1.0f, 1.0f);
        this->cubeShader->setVec3f("light.specular", 1.0f, 1.0f, 1.0f);
    }
}

void LightTexture::Draw()
{
    Scene3D::Draw();
}


void LightTexture::init()
{
    this->getRenderContext()->GetCtxCamera()->SetPosition(glm::vec3(0.0f,1.0f,0.0f));
    // add light
    this->light = new Cube;
    this->light->SetPosition(glm::vec3(1.2f, 0.2f, -5.0f));
    this->light->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
    this->Add(this->light);

    diffuse = this->loadTexture("../assets/container2.png");
    specular = this->loadTexture("../assets/container2_specular.png");
    emission = this->loadTexture("../assets/matrix.jpg");
    // add cube
    this->cube = new Cube;
    this->cube->SetPosition(glm::vec3(0.0f, 0.0f, -6.0f));
    this->cube->SetRotation(35.0f, glm::vec3(0, 1, 0));
    this->cubeShader = new Shader("../shaders/lighting_maps.vert","../shaders/lighting_maps.frag");
    this->cube->SetShader(cubeShader);
    this->cubeShader->active();
    this->cubeShader->setInt("material.diffuse",0);
    this->cubeShader->setInt("material.specular",1);
    this->cubeShader->setInt("material.emission",2);
    this->Add(this->cube);
}


unsigned int LightTexture::loadTexture(std::string path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
