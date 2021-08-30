#include "TextureScene.h"

TextureScene::TextureScene()
{
    this->init();
    this->initProgarm();
}

void TextureScene::init()
{ 
    cameraPos = glm::vec3(0.0f,0.0f,5.0f);
    cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
    cameraUp = glm::vec3(0.0f,1.0f,0.0f);
    projection = glm::perspective(glm::radians(45.0f),800.0f/600.0f,1.0f,100.0f);
    model = glm::mat4(1.0);

    this->points = new float[24]{
        0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,
         0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,
    };
    glCreateBuffers(1,&VAO);
    glBindVertexArray(VAO);
    glCreateBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,24,this->points,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,false,3 * sizeof(float),0);
    glEnableVertexAttribArray(0);

    this->indies = new unsigned char[36]{
        0,1,3,3,1,2, // front
        2,1,6,7,2,6, //left
        3,0,5,4,3,5, //right
        7,6,4,4,6,5, // back
        7,2,3,4,2,3, // top
        6,1,0,5,1,0  // bottom
    };

    glCreateBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,36,indies,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,false,3 *sizeof(float),0);
    glEnableVertexAttribArray(0);
}


void TextureScene::initProgarm()
{
    ShaderLoader loader;
    Shader shaders[] = {{GL_VERTEX_SHADER, "./shaders/texture.vert"},
                        {GL_FRAGMENT_SHADER, "./shaders/texture.frag"}};
    this->program = loader.creatProgram(shaders);
    glUseProgram(program);


    
}

void TextureScene::setProgramParam()
{
    view = glm::lookAt(cameraPos,cameraPos +cameraFront,cameraUp);
    glm::mat4 mvp = projection * view * model;
    int mvpUniform = glGetUniformLocation(this->program,"mvpMat");
    glUniformMatrix4fv(mvpUniform,1,false,glm::value_ptr(mvp));
}



TextureScene::~TextureScene()
{
    glDeleteProgram(this->program);
    delete this->points;
}

void TextureScene::display()
{
    this->setProgramParam();
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_BYTE,0);
}