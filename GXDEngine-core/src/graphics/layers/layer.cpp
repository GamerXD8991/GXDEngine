// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "layer.h"
#include "../renderables/label.h"

namespace GXDEngine { namespace graphics {
	Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projMatrix) 
		: m_Renderer(renderer),	m_ProjectionMatrix(projMatrix), m_Shader(shader) {

		m_Shader->enable();
		m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
		m_Shader->disable();

	}

	Layer::~Layer() {
		//delete m_Shader;
		delete m_Renderer;

		for (size_t i = 0; i < m_Renderables.size(); ++i) {
			delete m_Renderables[i];
		}
	}



	void Layer::add(Renderable2D* renderable) {
		m_Renderables.push_back(renderable);
	}

	void Layer::render() {

		m_Shader->enable();

		m_Renderer->begin();

		for (Renderable2D* rend : m_Renderables) {
			rend->submit(m_Renderer);
		}

		m_Renderer->end();

		m_Renderer->flush();

		m_Shader->disable();
	}

} }
