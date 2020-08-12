#pragma once
#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "../font.h"

namespace GXDEngine { namespace graphics {
	
	class Renderable2D;

	class Renderer2D {
	protected:
		std::vector<maths::mat4> m_TFS; //m_TransformationStack
		const maths::mat4* m_TFBack;

	protected:
		Renderer2D()  {
			m_TFS.push_back(maths::mat4::identity());
			m_TFBack = &m_TFS.back();
		}
	public:
		inline void push(const maths::mat4& mat, bool override = false) {
			if (override) {
				m_TFS.push_back(mat);
				m_TFBack = &m_TFS.back();;
			} else { m_TFS.push_back(m_TFS.back() * mat); }
			m_TFBack = &m_TFS.back();
		}
		inline void pop()  {
			if (m_TFS.size() > 1) m_TFS.pop_back();
			m_TFBack = &m_TFS.back();
		}

		virtual void begin()  {}
		virtual void end()  {}
		virtual void submit(const Renderable2D* renderable) = 0;
		virtual void flush() = 0;
	
		virtual void drawString(const std::string& str, const maths::vec3 position, Font& font, const unsigned int color)  {}

	};

} }