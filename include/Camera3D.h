#ifndef __CAMERA_3D_H__
#define __CAMERA_3D_H__
#include "common.h"
#include "Object3D.h"

typedef struct PerspectiveCameraInfo
{
    float fov;
    float aspect;
    float near;
    float far;
    glm::vec3 cameraUp;
    glm::vec3 target;
    glm::vec3 cameraPosition;
} CAMERA_INFO, *PCAMERA_INFO;

class Camera3D
{
public:
    Camera3D(float fov, float aspect, float near, float far);

    void updateFOV(float fov);

    void updateProjection(float aspec);

    void SetPosition(glm::vec3 newPos);

    glm::mat4 getProjectionMatrix() const;

    glm::mat4 getViewMatrix() const;

    CAMERA_INFO GetCameraInfo() const;

    void LookAt(glm::vec3 target);

    void AddYawInput(float value);

    void AddPitchInput(float value);

    void AddRollInput(float value);

    void rotate(float angle, glm::vec3 axis);

private:
    float fieldOfView;
    float aspectio;
    float near;
    float far;

    glm::vec3 up;
    glm::vec3 lookTarget;
    glm::vec3 position;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
};

#endif
