// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )
#include "sprite.h"

namespace GXDEngine { namespace graphics {
		
	Sprite::Sprite(const float x, const float y, const float width, const float height, const unsigned int color)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color) {

	}

	Sprite::Sprite(const float x, const float y, const float width, const float height, Texture* texture)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xFFFFFFFF) {
		m_Texture = texture;
	}

	Sprite::~Sprite() {}
	

} }
