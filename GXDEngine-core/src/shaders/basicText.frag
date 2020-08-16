#version 460 core

layout (location = 0) out vec4 color;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D text[21];

void main()
{	
	//vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text[int(fs_in.tid - 0.5)], fs_in.uv).r);
    //color = fs_in.color * sampled;


	vec4 texColor = fs_in.color;
	if (fs_in.tid > 0.0) 
		texColor = fs_in.color * texture(text[int(fs_in.tid - 0.5)], fs_in.uv);
	
	color = texColor;
}