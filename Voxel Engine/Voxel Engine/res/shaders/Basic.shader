#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
uniform mat4 mvp;
uniform mat4 model;
uniform vec3 lightDir;

out float diff;
out vec3 fragPos;
out vec3 objectColor;

void main()
{
	gl_Position = mvp * position;
	vec3 norm = vec3(model * vec4(normal, 1.0f));
	diff = max(dot(norm, -normalize(lightDir)), 0.0f);
	objectColor = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in float diff;
in vec3 objectColor;

void main()
{
	vec3 objColor = vec3(0.0f, 0.0f, 1.0f);
	vec3 result = objColor * diff;
	result = result + objColor * 0.2f;
	color = vec4(result, 1.0f);
	//color = vec4(objColor, 1.0f);
};