#pragma once
#include <GLFW/glfw3.h>

struct WindowProps
{
	const char* Title;
	unsigned int Width, Height;

	WindowProps(
		const const char* title = "Voxel Engine",
		unsigned int width = 1280,
		unsigned int height = 720)
		: Title(title), Width(width), Height(height)
	{
	}
};

class Window {
public:
	Window(const WindowProps& props);
	~Window();
	void OnUpdate();
	bool IsRunning();

	unsigned int GetWidth() { return data.Width; }
	unsigned int GetHeight() { return data.Height; }

	GLFWwindow* GetWindow() { return window; }
	void Shutdown();
private:
	GLFWwindow* window;

	struct WindowData
	{
		const char* Title;
		unsigned int Width, Height;
	};	

	WindowData data;
};