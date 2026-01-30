#pragma once
#include<string>
#include<glm/glm.hpp>
#include<memory>

class Camera3D {
public:
	uint32_t m_id=0;
	uint32_t getID() const { return m_id; }
	static std::shared_ptr<Camera3D> Create(float cameraPos[3], float cameraTarget[3]);
	std::string m_name;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix=glm::mat4(1.0f);
	void updateViewMatrix();
	void moveCameraForward(float length);
	void moveCameraRight(float length);
	void moveCameraUp(float length);
	void setMoveSpeed(float speed);
	void setID(uint32_t id);
	void setNearFarPlanes(float nearPlane, float farPlane); 
	void setFOV(float fovDegrees);
private:
	Camera3D(float cameraPos[3],float cameraTarget[3]);
	glm::vec3 m_xaxis;
	glm::vec3 m_yaxis;
	glm::vec3 m_zaxis;
	glm::vec3 m_cameraFront;
	glm::vec3 m_currentPos;
	float m_moveSpeed = 0.1f;
	float m_deltaTime = 0.0f;
	float m_nearPlane = 0.1f;
	float m_farPlane = 100.0f;
	float m_fov = 45.0f;
};