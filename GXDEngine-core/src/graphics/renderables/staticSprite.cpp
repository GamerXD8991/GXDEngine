// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )
#include "staticSprite.h"

namespace GXDEngine { namespace graphics {
	
	StaticSprite::StaticSprite(float x, float y, float width, float height, maths::vec4& color, Shader& shader)
		: Renderable2D(maths::vec3(x,y,0), maths::vec2(width, height), 0), m_shader(shader) {

		setColor(color);

		m_VertexArray = new VertexArray();
		GLfloat vertices[] = {
			0, 0, 0,
			0, height, 0,
			width, height,  0,
			width, 0, 0
		};

		GLfloat colors[] = {
			color.m_x, color.m_y, color.m_z, color.m_w,
			color.m_x, color.m_y, color.m_z, color.m_w,
			color.m_x, color.m_y, color.m_z, color.m_w,
			color.m_x, color.m_y, color.m_z, color.m_w
		};

		m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer = new IndexBuffer(indices, 6);
	}
	
	StaticSprite::~StaticSprite() {
		delete m_VertexArray;
		delete m_IndexBuffer;
	}

} }