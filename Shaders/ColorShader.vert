#version 440
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 mvpMatrix;

out vec4 vertCol;

void main()
{
	gl_Position = mvpMatrix * vec4(position, 1.0);
	vertCol = color;
}