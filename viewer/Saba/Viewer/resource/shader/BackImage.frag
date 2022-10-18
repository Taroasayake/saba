#version 140

in vec2 UV;

// Ouput data
out vec3 color;

uniform sampler2D myTextureSampler;

void main()
{

	//color = vec3(1,0,0);
	
	color = texture( myTextureSampler, UV ).rgb;

}
