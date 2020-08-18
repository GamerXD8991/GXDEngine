// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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

	void Group::submit(Renderer2D* renderer) const {

		renderer->push(m_TransformationMatrix);
		
		for (const Renderable2D* rend : m_Renderables) {
			rend->submit(renderer);
		}

		renderer->pop();
	}
} }