#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_ViewDir;
	glm::mat4 m_ViewMatrix;

	float m_Speed = 0.005f;
public:
	Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
	~Camera();

	void ProcessInput(GLFWwindow *window);

	glm::vec3 GetPosition() const { return m_Position; }
	glm::vec3 GetUp() const { return m_Up; }
	glm::vec3 GetFront() const { return m_Front; }
	glm::vec3 GetViewDir() const { return m_ViewDir; }
	glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

	float GetSpeed() const { return m_Speed; }
};