#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 _uvCoord;
uniform mat4 mvp;
uniform mat4 model;
uniform vec3 lightDir;

out float diff;
out vec3 fragPos;
out vec3 objectColor;
out vec2 uvCoord;

//Maps a value in a range to another range
float map(float value, float min1, float max1, float min2, float max2)
{
	return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main()
{
	gl_Position = mvp * position;
	vec3 norm = vec3(model * vec4(normal, 1.0f));
	diff = map(dot(norm, -normalize(lightDir)), -1.0f, 1.0f, 0.1f, 1.0f);
	objectColor = color;
	uvCoord = _uvCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Texture;

in float diff;
in vec3 objectColor;
in vec2 uvCoord;

void main()
{
	vec4 texColor = texture(u_Texture, uvCoord);
	vec3 result = vec3(texColor.x, texColor.y, texColor.z) * diff;
	color = vec4(result, texColor.w);
};