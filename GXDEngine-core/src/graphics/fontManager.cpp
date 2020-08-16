// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "fontManager.h"

namespace GXDEngine { namespace graphics {

	std::vector<Font*> FontManager::m_Fonts;

	void FontManager::add(Font* font) {
		m_Fonts.push_back(font);
	}
	/*
	//	template void FontManager::add<const std::string&, const std::string&, const unsigned int>(const std::string&, const std::string&, const unsigned int);
	
	template<typename ...Args>
	void FontManager::add(Args&& ...args) {
		m_Fonts.emplace_back(std::forward<Args>(args));
	}
	*/

	void FontManager::clean() {
		for (Font* font : m_Fonts) {
			delete font;
		}
	}

	Font* FontManager::get(const std::string& name) {
		Font* res = nullptr;
		for (Font* font : m_Fonts) {
			if (font->getName() == name) {
				res = font;
				break;
			}
		}

		return res;
	}

	Font* FontManager::get(const std::string& name, unsigned int size) {
		Font* res = nullptr;
		for (Font* font : m_Fonts) {
			if (font->getSize() == size && font->getName() == name) {
				res = font;
				break;
			}
		}

		return res;
	}
} }