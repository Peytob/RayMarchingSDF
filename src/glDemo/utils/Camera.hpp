#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glm/vec3.hpp>

namespace OGLUtils
{

class Camera
{
public:
    Camera(const glm::vec3& position, const glm::vec3& frontVector, const float fov);
    ~Camera() = default;

    void setPosition(const glm::vec3& position);
    void move(const glm::vec3& difference);
    const glm::vec3& getPosition() const;

    void setFrontVector(const glm::vec3& frontVector);
    void rotateFrontVector(const glm::vec3& frontVector);
    const glm::vec3& getFrontVector() const;

    void setFov(const float fov);
    float getFov() const;

private:
    glm::vec3 position;
    glm::vec3 frontVector;
    float fov;
};

}

#endif
