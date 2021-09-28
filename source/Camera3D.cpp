#include "Camera3D.h"

Camera3D::Camera3D(float fov, float aspect, float cameraNear, float cameraFar)
{
    fieldOfView = fov;
    aspectio = aspect;
    nearCut = cameraNear;
    farCut = cameraFar;
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    WorldUp = up;
    front = glm::vec3(0.0f,0.0f,-1.0f);
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->Update();
}

void Camera3D::updateFOV(float fov)
{
    fieldOfView = fov;
}


void Camera3D::SetPosition(glm::vec3 newPos)
{
    position += newPos;
//    char buf[256];
//    memset(buf,0,sizeof (buf));
//    sprintf(buf,"Position(%.2f,%.2f,%.2f)\n",position.x,position.y,position.z);
//    std::cout << buf;
//    std::flush(std::cout);
}

void Camera3D::updateProjection(float aspec)
{
    aspectio = aspec;

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
    this->Update();
}

glm::mat4 Camera3D::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(fieldOfView),aspectio,nearCut,farCut);
}

glm::mat4 Camera3D::getViewMatrix() const
{
    return glm::lookAt(position,position + front,up);
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
    cameraInfo.right = Right;
    return cameraInfo;
}

void Camera3D::Update()
{
    Right = glm::normalize(glm::cross(front,WorldUp));
    up = glm::normalize(glm::cross(Right,front));
}

