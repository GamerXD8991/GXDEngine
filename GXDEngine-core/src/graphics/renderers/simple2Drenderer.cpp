// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )
#include "simple2Drenderer.h"

namespace GXDEngine { namespace graphics {
	
	void Simple2Drenderer::submit(const Renderable2D* renderable) {
		m_renderQueue.push_back((StaticSprite*) renderable);
	}

	void Simple2Drenderer::flush() {
		while (!m_renderQueue.empty()) {
			const StaticSprite* sSprite = m_renderQueue.front();
			const IndexBuffer* IBO = sSprite->getIBO();
			sSprite->getVAO()->bind();
			IBO->bind();

			sSprite->getShader().setUniformMat4("ml_matrix", maths::mat4::translation(sSprite->getPosition()));
			glDrawElements(GL_TRIANGLES, IBO->getCount(), GL_UNSIGNED_SHORT, 0);

			IBO->unbind();
			sSprite->getVAO()->unbind();
			m_renderQueue.pop_front();
		}
	}
}}