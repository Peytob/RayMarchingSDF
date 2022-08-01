#include <glDemo/utils/Camera.hpp>

#include <glm/gtx/common.hpp>
#include <glm/geometric.hpp>

using namespace OGLUtils;

Camera::Camera(const glm::vec3& position, const glm::vec3& frontVector, const float fov) :
    position(position), frontVector(frontVector), fov(fov) {

}

void Camera::setPosition(const glm::vec3& position) {
    this->position = position;
}

void Camera::move(const glm::vec3& difference) {
    this->position += difference;
}

const glm::vec3& Camera::getPosition() const {
    return position;
}

void Camera::setFrontVector(const glm::vec3& frontVector) {
    this->frontVector = glm::normalize(frontVector);
}

void Camera::rotateFrontVector(const glm::vec3& frontVector) {
    setFrontVector(this->frontVector + frontVector);
}

const glm::vec3& Camera::getFrontVector() const {
    return this->frontVector;
}

void Camera::setFov(const float fov) {
    this->fov = glm::fmod(fov, 2.0f);
}

float Camera::getFov() const {
    return fov;
}
