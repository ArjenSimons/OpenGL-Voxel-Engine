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
	//Press shift to move faster
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		m_CurrentSpeed = m_FastSpeed;
	else m_CurrentSpeed = m_Speed;

	//Move using WASD keys
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

	//Set prefious positions to current position if it's the first time this method is called
	if (firstCursorMovement)
	{
		prefXPos = xPos;
		prefYPos = yPos;
		firstCursorMovement = false;
	}

	//Get the amount of mouse movement
	deltaX = xPos - prefXPos;
	deltaY = yPos - prefYPos;
	prefXPos = xPos;
	prefYPos = yPos;

	deltaX *= m_Sensitivity;
	deltaY *= m_Sensitivity;
	 
	m_Pitch -= deltaY;
	m_Yaw += deltaX;
	
	//Limit the Pitch to prevent the view flipping upside down
	m_Pitch = glm::clamp(m_Pitch, -89.9f, 89.9f);

	glm::vec3 dir;

	//Calculate the rotation on the x, y and z axis. 
	dir.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
	dir.y = glm::sin(glm::radians(m_Pitch));
	dir.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(dir);
}

void Camera::SetTime()
{
	//Get the delta time (this is used to make movement framerate independent)
	m_CurrentFrame = glfwGetTime();
	m_DeltaTime = m_CurrentFrame - m_LastFrame;
	m_LastFrame = m_CurrentFrame;

	//Print the frame rate
	float frameRate;
	frameRate = 1 / m_DeltaTime;
	std::cout << frameRate << std::endl;
}
