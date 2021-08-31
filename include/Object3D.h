#ifndef __OBJECT_3D__
#define __OBJECT_3D__
#include "common.h"

class Object3D
{
public:
    Object3D();
    ~Object3D();
    void SetPosition(glm::vec3 newPos);
    void SetPosition(float x, float y, float z);
    glm::vec3 GetPosition() const;

    void SetRotation(float angle, glm::vec3 rotationAxis);
    glm::vec3 GetRotation() const;

    void SetScale(glm::vec3 scale);

    virtual void draw() = 0;
    virtual void Tick(float delta) = 0;

private:
    glm::vec3 position;
};

#endif
