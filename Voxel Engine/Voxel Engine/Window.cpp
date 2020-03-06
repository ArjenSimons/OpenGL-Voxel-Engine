#include <GL/glew.h>
#include "Window.h"
#include <iostream>

Window::Window(const WindowProps& props)
{
	if (!glfwInit())
	{
		std::cout << "Could not initialize GLFW!" << std::endl;
		exit(EXIT_FAILURE);
	}

	data.Title = props.Title;
	data.Width = props.Width;
	data.Height = props.Height;

	window = glfwCreateWindow(props.Width, props.Height, props.Title, NULL, NULL);
	printf("Creating %s window | Width: %i  height: %i\n", props.Title, props.Width, props.Height);
	if (!window)
	{
		std::cout << "Error initializeng window and OpenGL context" << std::endl;
		Shutdown();
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		Shutdown();
		exit(EXIT_FAILURE);
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
}

Window::~Window()
{
	Shutdown();
}

void Window::OnUpdate()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::IsRunning()
{
	return !glfwWindowShouldClose(window);
}

void Window::Shutdown()
{
	glfwTerminate();
}
