#pragma optimize( "f", on )
#include "simple2Drenderer.h"

namespace GXDEngine { namespace graphics {
	
	void Simple2Drenderer::submit(const Renderable2D* renderable) {
		m_renderQueue.push_back((StaticSprite*) renderable);
	}

	void Simple2Drenderer::flush() {
		while (!m_renderQueue.empty()) {
			const StaticSprite* sSprite = m_renderQueue.front();
			sSprite->getVAO()->bind();
			sSprite->getIBO()->bind();

			sSprite->getShader().setUniformMat4("ml_matrix", maths::mat4::translation(sSprite->getPosition()));
			glDrawElements(GL_TRIANGLES, sSprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);

			sSprite->getIBO()->unbind();
			sSprite->getVAO()->unbind();
			m_renderQueue.pop_front();
		}
	}
}}