#ifndef __CAMERA_3D_H__
#define __CAMERA_3D_H__
#include "common.h"
#include "Object3D.h"

typedef struct PerspectiveCameraInfo
{
    float fov;
    float aspect;
    float nearCut;
    float farCut;
    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 cameraPosition;
    glm::vec3 right;
} CAMERA_INFO, *PCAMERA_INFO;

class Camera3D
{
public:
    Camera3D(float fov, float aspect, float near, float far);

    void updateFOV(float fov);

    void SetPosition(glm::vec3 newPos);

    void updateProjection(float aspec);

    glm::mat4 getProjectionMatrix() const;

    glm::mat4 getViewMatrix() const;

    CAMERA_INFO GetCameraInfo() const;

    void AddYawInput(float value);

    void AddPitchInput(float value);

    void AddRollInput(float value);

private:
    float fieldOfView;
    float aspectio;
    float nearCut;
    float farCut;

    glm::vec3 up;
    glm::vec3 front;
    glm::vec3 position;
    glm::vec3 WorldUp;
    glm::vec3 Right;

    void rotate(float angle, glm::vec3 axis);
    void Update();
};

#endif
