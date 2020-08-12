#pragma once
#pragma optimize( "f", on )

#include "renderer2d.h"
#include "../renderables/staticSprite.h"

namespace GXDEngine { namespace graphics {
	
	class Simple2Drenderer : public Renderer2D {
	private:
		std::deque<const StaticSprite*> m_renderQueue;

	public: 
		void submit(const Renderable2D* renderable) override;
		void flush() override;
	};

} }