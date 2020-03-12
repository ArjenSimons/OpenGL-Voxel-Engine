#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up)
	: m_Position(position), m_Front(front), m_Up(up)
{
	m_ViewDir = glm::normalize(position + front);
	m_ViewMatrix = glm::lookAt(position, m_ViewDir, up);
}

Camera::~Camera()
{
}

void Camera::ProcessInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Position -= m_Speed * m_ViewDir;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_Position += m_Speed * m_ViewDir;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_Position -= m_Speed * glm::normalize(glm::cross(m_Front, m_Up));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_Position += m_Speed * glm::normalize(glm::cross(m_Front, m_Up));

	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}
