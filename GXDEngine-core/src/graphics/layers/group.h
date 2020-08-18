#pragma once
#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "../renderables/renderable2D.h"

namespace GXDEngine { namespace graphics {
	
	class Group : public Renderable2D {
	private:
		std::vector<Renderable2D*> m_Renderables;
		maths::mat4 m_TransformationMatrix;
	public:
		Group(const maths::mat4& transform);
		~Group();

		void add(Renderable2D* rend);
		void submit(Renderer2D* renderer) const ;
	};

} }