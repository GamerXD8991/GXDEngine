#pragma once
#pragma optimize( "f", on )

#include "../stdafx.h"

namespace GXDEngine { namespace graphics {
		
	class Font {
	private:

		ftgl::texture_atlas_t* m_FTAtlas;
		ftgl::texture_font_t* m_FTFont;
		float m_Size;

		std::string m_Name;
		const char* m_Filename;

	public:
		Font(const std::string& name, const char* filename, const float fontSize);
		~Font();

		inline const std::string& getName() const  { return m_Name; }
		inline const char* getFilename() const  { return m_Filename; }
		inline const float getSize() const  { return m_Size; }
		
		inline const unsigned int getID() const  { return (unsigned int) m_FTAtlas->id; }
		inline const unsigned int getDepth() const  { return (unsigned int) m_FTAtlas->depth; }
		inline const GLsizei getAtlasWidth() const  { return (GLsizei) m_FTAtlas->width; }
		inline const GLsizei getAtlasHeight() const  { return (GLsizei) m_FTAtlas->height; }
		inline const unsigned char* getAtlasData() const  { return m_FTAtlas->data;  }

		void getGlyphVaules(const char c, int pos_i, const std::string& str, float& kerning, int& offset_x, int& offset_y, unsigned long long& width, unsigned long long& height, float& s0, float& t0, float& s1, float& t1, float& advance_x);

	};

} }
