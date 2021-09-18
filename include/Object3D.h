#ifndef __OBJECT_3D__
#define __OBJECT_3D__
#include "common.h"

class RenderContext;

class Object3D
{
public:
    unsigned int UUID;
    Object3D();
    void SetPosition(glm::vec3 newPos);
    void SetRenderContext(RenderContext* ctx){
        this->renderCtx = ctx;
    }
    RenderContext * getRenderContext() {return this->renderCtx;};
    glm::vec3 GetPosition() const
    {
        return glm::vec3(position.x, position.y, position.z);
    };

    void SetRotation(float angle, glm::vec3 rotationAxis);

    void RotateX(float angle) { SetRotation(angle, glm::vec3(1.0f, 0.0f, 0.0f)); };
    void RotateY(float angle) { SetRotation(angle, glm::vec3(0.0f, 1.0f, 0.0f)); };
    void RotateZ(float angle) { SetRotation(angle, glm::vec3(0.0f, 0.0f, 1.0f)); };

    glm::vec3 GetRotation() const
    {
        return glm::vec3(rotation.x, rotation.y, rotation.z);
    };

    void SetScale(glm::vec3 scale);
    glm::vec3 GetScale() const
    {
        return glm::vec3(scale.x, scale.y, scale.z);
    };

    glm::mat4 GetModelMatrix() const;
    virtual ~Object3D(){};
    virtual void Draw() = 0;
    virtual void Tick(float delta) = 0;
    virtual void Destroy() = 0;
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 modelMat;
    RenderContext * renderCtx;
};

#endif
