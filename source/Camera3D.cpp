#include "Camera3D.h"

Camera3D::Camera3D(float fov, float aspect, float cameraNear, float cameraFar)
{
    fieldOfView = fov;
    aspectio = aspect;
    nearCut = cameraNear;
    farCut = cameraFar;
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    front = glm::vec3(0.0f,0.0f,-1.0f);
    position = glm::vec3(-6.0f, 6.0f, 20.0f);
    projectionMatrix = glm::perspective(fieldOfView,aspectio,this->nearCut,this->farCut);
    viewMatrix = glm::lookAt(this->position,this->position + this->front,this->up);
}

void Camera3D::updateFOV(float fov)
{
    fieldOfView = fov;
    this->updateProjection(aspectio);
}

void Camera3D::updateProjection(float aspec)
{
    projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspec, nearCut, farCut);
}

void Camera3D::SetPosition(glm::vec3 newPos)
{
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;
    this->LookAt(front);
}

/**
 * @brief Camera3D::AddYawInput 添加偏航角
 * @param value
 */
void Camera3D::AddYawInput(float value)
{
    this->rotate(value, glm::vec3(0.0f, 1.0f, 0.0f));
}

/**
 * @brief Camera3D::AddPitchInput 添加俯仰角
 * @param value
 */
void Camera3D::AddPitchInput(float value)
{
    this->rotate(value, glm::vec3(1.0f, 0.0f, 0.0f));
}

/**
 * @brief Camera3D::AddRollInput 添加翻滚角
 * @param value
 */
void Camera3D::AddRollInput(float value)
{
    this->rotate(value, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Camera3D::rotate(float angle, glm::vec3 axis)
{
    glm::vec3 dir = glm::normalize(front);
    glm::quat qua = glm::angleAxis(glm::degrees(angle),axis);
    glm::vec3 res = qua * dir;
//    std::cout << "front("<< front.x << "," << front.y << "," << front.z << ")." << "res({x:" << res.x  << ",y:" << res.y << "," << res.z <<"})\n";
//    std::flush(std::cout);
    front = res;
    this->LookAt(front);
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
    cameraInfo.nearCut = nearCut;
    cameraInfo.farCut = farCut;
    cameraInfo.up = up;
    cameraInfo.front = this->front;
    cameraInfo.cameraPosition = position;
    return cameraInfo;
}

void Camera3D::LookAt(glm::vec3 target)
{
    viewMatrix = glm::lookAt(position,this->position + target, up);
}
