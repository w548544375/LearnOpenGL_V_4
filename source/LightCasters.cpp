#include "LightCasters.h"
#include "RenderContext.h"

LightCasters::LightCasters() : Scene3D()
{
    this->init();
}

LightCasters::~LightCasters()
{

}

void LightCasters::Tick(float delta)
{
    Scene3D::Tick(delta);
        Object3D * obj = this->Get(0);
        Cube * cube = (Cube *)obj;
        Shader * cubeShader = cube->GetShader();
        cubeShader->active();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,this->diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,this->specular);
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D,this->emission);

        CAMERA_INFO camera = this->getRenderContext()->GetCtxCamera()->GetCameraInfo();
        glm::vec3 cameraPos = camera.cameraPosition;
        cubeShader->setVec3f("light.direction", camera.front.x,camera.front.y,camera.front.z);
        cubeShader->setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        cubeShader->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        cubeShader->setVec3f("light.position",cameraPos.x,cameraPos.y,cameraPos.z);
        cubeShader->setVec3f("viewPos",cameraPos.x,cameraPos.y,cameraPos.z);
        cubeShader->setFloat("material.shinness",32.0f);
        cubeShader->setVec3f("light.ambient", 0.2f, 0.2f, 0.2f);
        cubeShader->setVec3f("light.diffuse", 1.0f, 1.0f, 1.0f);
        cubeShader->setVec3f("light.specular", 1.0f, 1.0f, 1.0f);
        cubeShader->setFloat("light.constant", 1.0f);
        cubeShader->setFloat("light.linear", 0.09f);
        cubeShader->setFloat("light.quadratic", 0.032f);

}

void LightCasters::Draw()
{
    Scene3D::Draw();
}


void LightCasters::init()
{
    this->getRenderContext()->GetCtxCamera()->SetPosition(glm::vec3(0.0f,0.0f,6.0f));
    // add light
//    this->light = new Cube;
//    this->light->SetPosition(glm::vec3(1.2f, 0.2f, -5.0f));
//    this->light->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
//    this->Add(this->light);

    diffuse = this->loadTexture("../assets/container2.png");
    specular = this->loadTexture("../assets/container2_specular.png");
//    emission = this->loadTexture("../assets/matrix.jpg");
    // add cube
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    Shader * cubeShader = new Shader("../shaders/light_casters.vert","../shaders/light_casters.frag");
    cubeShader->active();
    cubeShader->setInt("material.diffuse",0);
    cubeShader->setInt("material.specular",1);
//    cubeShader->setInt("material.emission",2);

    for(int i = 0;i < 10;i++) {
        Cube * cube = new Cube;
        cube->SetPosition(cubePositions[i]);
        float angle = 20.0f * i;
        cube->SetRotation(angle, glm::vec3(0, 1, 0));
        cube->SetShader(cubeShader);
        this->Add(cube);
    }
}


unsigned int LightCasters::loadTexture(std::string path)
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
