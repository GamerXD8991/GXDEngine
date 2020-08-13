// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "label.h"

namespace GXDEngine { namespace graphics {



	Label::Label(const float x, const float y, const unsigned int color, Font* font, const std::string& text)
		: Renderable2D(), m_String(text), m_Font(font) {
		m_Pos = maths::vec3(x, y, 0);
		m_Color = color;
	}



	void Label::submit(Renderer2D* renderer) const {
		renderer->drawString(m_String, m_Pos, *m_Font, m_Color );
	}



	void Label::setText(const std::string& text) {
		m_String = text;
		//A_memcpy(&m_String, &text, sizeof(text));
	}

	void Label::setPosition(const float x, const float y) {
		m_Pos = maths::vec3(x, y, 0);
	}

	const maths::vec3& Label::getPosition() const  {
		return m_Pos;
	}
} }