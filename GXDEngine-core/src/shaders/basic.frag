#version 460 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA {
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main() {
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	vec4 texColor = fs_in.color;
	switch(int(fs_in.tid - 0.5))
	{
		case 1:
			texColor = fs_in.color * texture(textures[0], fs_in.uv);
			break;
		case 2:
			texColor = fs_in.color * texture(textures[1], fs_in.uv);
			break;
		case 3:
			texColor = fs_in.color * texture(textures[2], fs_in.uv);
			break;
		case 4:
			texColor = fs_in.color * texture(textures[3], fs_in.uv);
			break;
		case 5:
			texColor = fs_in.color * texture(textures[4], fs_in.uv);
			break;
		case 6:
			texColor = fs_in.color * texture(textures[5], fs_in.uv);
			break;
	}
	color = texColor * intensity;
}