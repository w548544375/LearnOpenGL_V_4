#ifndef __CAMERA_3D_H__
#define __CAMERA_3D_H__
#include "common.h"

class Camera3D
{
public:
    void updateProjection(float fov, float aspec, float near, float far);
};

#endif
