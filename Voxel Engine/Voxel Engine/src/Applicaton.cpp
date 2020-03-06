#include <GL/glew.h>
#include "Window.h"
#include <iostream>

int main(void)
{
	Window window = Window::Window(WindowProps());

	float positions[6]{
		-0.5f, -0.5,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int buffer;
	glGenBuffers(2, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	while (window.IsRunning())
	{
		/*Render*/
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		window.OnUpdate();
	}

	window.Shutdown();

	return 0;
}