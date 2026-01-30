#include "camera.hpp"
#include"../engine_state.hpp"
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

std::shared_ptr<Camera3D> Camera3D::Create(float cameraPos[3], float cameraTarget[3]){
    auto cam = std::shared_ptr<Camera3D>(new Camera3D(cameraPos, cameraTarget));
    GEngine().activeCamera = cam;
    return cam;
}

Camera3D::Camera3D(float cameraPos[3], float cameraTarget[3]) {
    m_currentPos = glm::vec3(cameraPos[0], cameraPos[1], cameraPos[2]);
    glm::vec3 target = glm::vec3(cameraTarget[0], cameraTarget[1], cameraTarget[2]);
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    m_zaxis = glm::normalize(m_currentPos - target);
    m_xaxis = glm::normalize(glm::cross(worldUp, m_zaxis));
    m_yaxis = glm::cross(m_zaxis, m_xaxis);
    m_cameraFront = -m_zaxis;
	int aspectRatio = GEngine().width / GEngine().height;
	m_projectionMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(aspectRatio), m_nearPlane, m_farPlane);
    updateViewMatrix();
}

void Camera3D::updateViewMatrix() {
    m_viewMatrix = glm::lookAt(m_currentPos, m_currentPos + m_cameraFront, glm::vec3(0, 1, 0));
}

void Camera3D::moveCameraForward(float length) {
    float velocity = length * static_cast<float>(GEngine().deltaTime);
    m_currentPos += m_cameraFront * velocity;
    updateViewMatrix();
}
void Camera3D::moveCameraRight(float length){
	float velocity = length * static_cast<float>(GEngine().deltaTime);
	m_currentPos += m_xaxis * velocity;
	updateViewMatrix();
}

void Camera3D::moveCameraUp(float length){
    float velocity = length * static_cast<float>(GEngine().deltaTime);
    m_currentPos += m_yaxis * velocity;
    updateViewMatrix();
}

void Camera3D::setMoveSpeed(float speed){
	m_moveSpeed = speed; 
}

void Camera3D::setID(uint32_t id){
	m_id = id;
}

void Camera3D::setNearFarPlanes(float nearPlane, float farPlane){
    m_nearPlane = nearPlane;
	m_farPlane = farPlane;
}

void Camera3D::setFOV(float fovDegrees){
    m_fov = fovDegrees;
    int aspectRatio = GEngine().width / GEngine().height;
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), static_cast<float>(aspectRatio), m_nearPlane, m_farPlane);
}

