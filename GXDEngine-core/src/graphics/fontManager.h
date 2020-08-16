#pragma once
#pragma optimize( "f", on )

#include "../stdafx.h"
#include "font.h"

namespace GXDEngine { namespace graphics {

	class FontManager {
	private:
		static std::vector<Font*> m_Fonts;

	public:
		static void add(Font* font);
		//template<typename ...Args>
		//void add(Args&& ...args);
		static void clean();
		static Font* get(const std::string& name);
		static Font* get(const std::string& name, unsigned int size);

	private:
		FontManager();
	};

} }