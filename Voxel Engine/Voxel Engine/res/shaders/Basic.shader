#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 mvp;

void main()
{
	gl_Position = mvp * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(0.0, 0.0, 1.0, 1.0);
};

