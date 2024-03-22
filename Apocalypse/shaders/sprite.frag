#version 330 core

in vec2 passedTexturePosition;
out vec4 fragmentColour;

uniform sampler2D texture0;

void main()
{

	vec4 textureColour = texture(texture0, passedTexturePosition);
	if (textureColour.rgb == vec3(0.0, 0.0, 0.0))
	{
		discard;
	}

	fragmentColour = textureColour;
}

