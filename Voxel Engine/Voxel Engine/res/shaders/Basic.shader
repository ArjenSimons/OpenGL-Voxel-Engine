#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 mvp;
uniform vec3 lightDir;

out float diff;

void main()
{
	gl_Position = mvp * position;
	diff = max(dot(normalize(normal), normalize(lightDir)), 0.0f);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in float diff;

void main()
{
	vec3 objectColor = vec3(0.0f, 0.0f, 1.0f);
	vec3 result = objectColor * 1;
	result = result + vec3(0, 0, 0.1f);
	//color = vec4(vec3(diff, diff, diff), 1.0f);
	color = vec4(result, 1.0f);
};