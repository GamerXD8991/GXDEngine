#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "group.h"

namespace GXDEngine { namespace graphics {
	
	Group::Group(const maths::mat4& transform) 
		: m_TransformationMatrix(transform) {}

	Group::~Group() {
		for (Renderable2D* rend : m_Renderables) {
			delete rend;
		}
	}


	void Group::add(Renderable2D* rend) {
		m_Renderables.push_back(rend);
	}

	void Group::submit(Renderer2D* renderer) const  {

		renderer->push(m_TransformationMatrix);
		
		for (const Renderable2D* rend : m_Renderables) {
			rend->submit(renderer);
		}

		renderer->pop();
	}

} }