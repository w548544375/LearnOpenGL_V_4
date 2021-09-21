#include "SimpleCubeScene.h"
#include "RenderContext.h"
SimpleCubeScene::SimpleCubeScene() : Object3D()
{
    glEnable(GL_DEPTH_TEST);
    float vertics[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    glGenVertexArrays(1,&this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1,&this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER,this->VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof (vertics),vertics,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5 *sizeof (float),0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof (float),(void *)(3 *sizeof(float)));
    glEnableVertexAttribArray(1);


    glGenTextures(1,&texture0);
    glBindTexture(GL_TEXTURE_2D,texture0);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_CLAMP_TO_EDGE);

    int width,height,channel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * data = stbi_load("./assets/TexturesCom_MetalFloorsPainted0012_1_seamless_S.jpg",&width,&height,&channel,0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);

    shader =new Shader("./shaders/texture.vert","./shaders/texture.frag");
    shader->active();
    shader->setInt("texture",0);

}


void SimpleCubeScene::Tick(float delta)
{
//    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,this->texture0);
    shader->active();
//    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f/450.0f, 0.1f, 100.0f);
    glm::mat4 projection = this->getRenderContext()->GetCtxCamera()->getProjectionMatrix();
//    glm::mat4 view = glm::lookAt(glm::vec3(0.0f,2.0f,3.0f),glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 view = this->getRenderContext()->GetCtxCamera()->getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,this->GetPosition());
    glm::mat4 mvp = projection * view *model;
    shader->setMat4("mvpMat",mvp);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


SimpleCubeScene::~SimpleCubeScene()
{
    glDeleteVertexArrays(1,&this->VAO);
    glDeleteBuffers(1,&this->VBO);
}
