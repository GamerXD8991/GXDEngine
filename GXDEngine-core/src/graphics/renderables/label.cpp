// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )


#include "label.h"
#include "../fontManager.h"

namespace GXDEngine { namespace graphics {



	Label::Label(const float x, const float y, const unsigned int color, Font* font, const rapidstring& text)
		: Renderable2D(), m_String(text), m_Font(font) {
		m_Pos = maths::vec3(x, y, 0);
		m_Color = color;
	}

	Label::Label(const float x, const float y, const unsigned int color, const std::string& font, const rapidstring& text)
		: Renderable2D(), m_String(text) , m_Font(FontManager::get(font)) {
		m_Pos = maths::vec3(x, y, 0);
		m_Color = color;
	}

	Label::Label(const float x, const float y, const unsigned int color, const std::string& font, const unsigned int size, const rapidstring& text)
		: Renderable2D(), m_String(text), m_Font(FontManager::get(font, size)) {
		m_Pos = maths::vec3(x, y, 0);
		m_Color = color;
	}



	void Label::setText(const rapidstring& text) {
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