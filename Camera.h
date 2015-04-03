#pragma once

#include "OpenGL.h"
#include "Buffer.h"

class Player;

class Camera {
public:
    Camera();
    Camera(Camera &&move);
    // note: does not do any checking on up vector
    void updateView(float eyeX, float eyeY, float eyeZ,
                    float dirX, float dirY, float dirZ,
                    float up_X, float up_Y, float up_Z);
    void updateView(const Player &player, float eyeZ);
    void updateProj(float fov, float aspect, float znear, float zfar);
    GLint getBindingPoint() const;
protected:
    GLint binding_point;
    UniformBuffer ubo;
};