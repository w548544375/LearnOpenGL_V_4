#include "Object3D.h"

Object3D::Object3D()
{
    modelMat = glm::mat4(1.0f);
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
}

void Object3D::SetPosition(glm::vec3 newPos)
{
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;
    modelMat = glm::translate(modelMat, position);
}

void Object3D::SetRotation(float angle, glm::vec3 rotationAxis)
{
    if (rotationAxis.x == 0.0f)
        rotation.x += angle;
    if (rotationAxis.y == 0.0f)
        rotation.y += angle;
    if (rotationAxis.z == 0.0f)
        rotation.z += angle;
    modelMat = glm::rotate(modelMat, angle, rotationAxis);
}

void Object3D::SetScale(glm::vec3 sc)
{
    scale.x = sc.x;
    scale.y = sc.y;
    scale.z = sc.z;
    modelMat = glm::scale(modelMat, scale);
}

glm::mat4 Object3D::GetModelMatrix() const
{
    return modelMat;
}