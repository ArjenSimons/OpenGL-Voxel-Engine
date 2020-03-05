#include "Window.h"
#include <iostream>

int main(void)
{
	Window window = Window::Window(WindowProps());
	while (window.IsRunning())
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		window.OnUpdate();
	}

	glfwTerminate();
	return 0;
}