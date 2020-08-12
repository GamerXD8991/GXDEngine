#pragma once
#pragma optimize( "f", on )

#include "renderable2D.h"

namespace GXDEngine { namespace graphics {
	
	class Sprite : public Renderable2D {
	private:
	public:
		Sprite(const float x, const float y, const float width, const float height, const unsigned int color);
		Sprite(const float x, const float y, const float width, const float height, Texture* texture);
		~Sprite();
	};

} }
