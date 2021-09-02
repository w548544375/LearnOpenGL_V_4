#include "Camera3D.h"

Camera3D::Camera3D(float fov, float aspect, float nearCut, float farCut)
{
    fieldOfView = fov;
    aspectio = aspect;
    near = nearCut;
    far = farCut;
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    lookTarget = glm::vec3(0.0f, 0.0f, -1.0f);
    position = glm::vec3(0.0f, 0.0f, 2.0f);
    this->updateProjection(aspectio);
    this->LookAt(lookTarget);
}

void Camera3D::updateFOV(float fov)
{
    fieldOfView = fov;
    this->updateProjection(aspectio);
}

void Camera3D::updateProjection(float aspec)
{
    projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspec, near, far);
}

void Camera3D::SetPosition(glm::vec3 newPos)
{
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;
    this->LookAt(lookTarget);
}

// yaw 偏航角
void Camera3D::AddYawInput(float value)
{
    this->rotate(value, glm::vec3(0.0f, 1.0f, 0.0f));
}

// pitch 俯仰角
void Camera3D::AddPitchInput(float value)
{
    this->rotate(value, glm::vec3(1.0f, 0.0f, 0.0f));
}

//roll 翻滚角
void Camera3D::AddRollInput(float value)
{
    this->rotate(value, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera3D::rotate(float angle, glm::vec3 axis)
{
    glm::mat4 rotMat(1.0);
    glm::vec4 origin(lookTarget, 1.0);
    rotMat = glm::rotate(rotMat, glm::radians(angle), axis);
    origin = rotMat * origin;
    lookTarget.x = origin.x;
    lookTarget.y = origin.y;
    lookTarget.z = origin.z;
    this->LookAt(lookTarget);
}

glm::mat4 Camera3D::getProjectionMatrix() const
{
    return projectionMatrix;
}

glm::mat4 Camera3D::getViewMatrix() const
{
    return viewMatrix;
}

CAMERA_INFO Camera3D::GetCameraInfo() const
{
    PerspectiveCameraInfo cameraInfo;
    cameraInfo.fov = fieldOfView;
    cameraInfo.aspect = aspectio;
    cameraInfo.near = near;
    cameraInfo.far = far;
    cameraInfo.cameraUp = up;
    cameraInfo.target = lookTarget;
    cameraInfo.cameraPosition = position;
    return cameraInfo;
}

void Camera3D::LookAt(glm::vec3 target)
{
    viewMatrix = glm::lookAt(position, position + target, up);
}