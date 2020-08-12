#pragma once
#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "../renderers/renderer2D.h"
#include "../shader.h"

namespace GXDEngine { namespace graphics {
	
	class Layer {
	protected:
		Renderer2D* m_Renderer;
		std::vector<Renderable2D*> m_Renderables;
		Shader* m_Shader;
		maths::mat4 m_ProjectionMatrix;
	protected:
		Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projMatrix);
	
	public:
		virtual ~Layer();

		inline void push(maths::mat4& mat) { m_Renderer->push(mat); }
		inline void pop()  { m_Renderer->pop(); }

		virtual void add(Renderable2D* renderable);
		virtual void render();

		inline const Renderer2D* getRenderer() const  { return m_Renderer; }
		inline const std::vector<Renderable2D*>& getRenderables() const  { return m_Renderables; }
	};

} }