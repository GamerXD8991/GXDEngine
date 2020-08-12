#pragma optimize( "f", on )

#include "font.h"

namespace GXDEngine { namespace graphics {
		
	Font::Font(const std::string& name, const char* filename, const float fontSize) 
		: m_Name(name),	m_Filename(filename), m_Size(fontSize) {
		//const char* filename = "SourceSansPro-Regular.ttf";
		m_FTAtlas = ftgl::texture_atlas_new(350, 350, 2);
		m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, fontSize, filename);

		if (!&m_FTAtlas->id)
		{
			glGenTextures(1, &m_FTAtlas->id);
		}

		glBindTexture(GL_TEXTURE_2D, m_FTAtlas->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Font::~Font() {

	}



	void Font::getGlyphVaules(const char c, int pos_i, const std::string& str, float& kerning, int& offset_x, int& offset_y, unsigned long long& width, unsigned long long& height, float& s0, float& t0, float& s1, float& t1, float& advance_x)  {
		ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(m_FTFont, &c);
		if (glyph != NULL) {

			kerning = ftgl::texture_glyph_get_kerning(glyph, str.c_str() + pos_i - 1);

			offset_x = glyph->offset_x;
			offset_y = glyph->offset_y;
			width = glyph->width;
			height = glyph->height;

			s0 = glyph->s0;
			t0 = glyph->t0;
			s1 = glyph->s1;
			t1 = glyph->t1;

			advance_x = glyph->advance_x;
		}
	}

	

} }
