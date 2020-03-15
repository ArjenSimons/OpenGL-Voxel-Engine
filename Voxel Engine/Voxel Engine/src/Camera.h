#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::mat4 m_ViewMatrix;

	float const m_Speed = 6.0f;
	float const m_Sensitivity = 0.1f;

	float m_Yaw;
	float m_Pitch;
	float deltaX;
	float deltaY;
	float prefXPos;
	float prefYPos;
	bool firstCursorMovement = true;

	float m_DeltaTime;
	float m_CurrentFrame;
	float m_LastFrame;
public:
	Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up);
	~Camera();

	void ProcessInput(GLFWwindow *window);

	glm::vec3 GetPosition() const { return m_Position; }
	glm::vec3 GetUp() const { return m_Up; }
	glm::vec3 GetFront() const { return m_Front; }
	glm::vec3 GetViewDir() const { return m_Position + m_Front; }
	glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

	float GetSpeed() const { return m_Speed * m_DeltaTime; }
private:
	void CalculateDirection(GLFWwindow* window);
	void CalculatePosition(GLFWwindow* window);
	void SetTime();
};