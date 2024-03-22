#version 330 core

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 texturePosition;

uniform mat4 ortho;

out vec2 passedTexturePosition;

void main()
{
	passedTexturePosition = texturePosition;
	gl_Position = ortho * vec4(vertexPosition.x, vertexPosition.y, 0.0, 1.0);
}

