#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
	: m_Position(position), m_Front(front), m_Up(up)
{
	m_ViewMatrix = glm::lookAt(position, GetViewDir(), up);
	m_LastFrame = glfwGetTime();
	m_Yaw = -90;
	m_Pitch = 0;
}

Camera::~Camera()
{
}

void Camera::ProcessInput(GLFWwindow* window)
{
	SetTime();

	CalculatePosition(window);
	CalculateDirection(window);

	m_ViewMatrix = glm::lookAt(m_Position, GetViewDir(), m_Up);
}

void Camera::CalculatePosition(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		m_CurrentSpeed = m_FastSpeed;
	else m_CurrentSpeed = m_Speed;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Position += GetSpeed() * m_Front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_Position -= GetSpeed() * m_Front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_Position -= GetSpeed() * glm::normalize(glm::cross(m_Front, m_Up));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_Position += GetSpeed() * glm::normalize(glm::cross(m_Front, m_Up));
}

void Camera::CalculateDirection(GLFWwindow* window)
{
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	if (firstCursorMovement)
	{
		prefXPos = xPos;
		prefYPos = yPos;
		firstCursorMovement = false;
	}

	deltaX = xPos - prefXPos;
	deltaY = yPos - prefYPos;
	prefXPos = xPos;
	prefYPos = yPos;

	deltaX *= m_Sensitivity;
	deltaY *= m_Sensitivity;
	 
	m_Pitch -= deltaY;
	m_Yaw += deltaX;
	
	m_Pitch = glm::clamp(m_Pitch, -89.9f, 89.9f);

	glm::vec3 dir;

	dir.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
	dir.y = glm::sin(glm::radians(m_Pitch));
	dir.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(dir);
}

void Camera::SetTime()
{
	m_CurrentFrame = glfwGetTime();
	m_DeltaTime = m_CurrentFrame - m_LastFrame;
	m_LastFrame = m_CurrentFrame;

	float frameRate;
	frameRate = 1 / m_DeltaTime;
	std::cout << frameRate << std::endl;
}
