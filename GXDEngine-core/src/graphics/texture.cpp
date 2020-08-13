// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "texture.h"

namespace GXDEngine { namespace graphics {

		Texture::Texture(const std::string& path) : m_Path(path) {
			
			m_TextureID = load();
		}
		Texture::~Texture(){}

		void Texture::bind() const  { glBindTexture(GL_TEXTURE_2D, m_TextureID); }
		void Texture::unbind() const  { glBindTexture(GL_TEXTURE_2D, 0); }



		GLuint Texture::load() {

			unsigned int bpp = 0;
			BYTE* pixels = ImgLoad::instance().loadImg(m_Path.c_str(), &m_Width, &m_Height, bpp);

			GLuint generatedTextureID;
			glGenTextures(1, &generatedTextureID);
			glBindTexture(GL_TEXTURE_2D, generatedTextureID);


			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			switch (bpp) {
			case 32: {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
				break;
			}
			case 24: {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
				break;
			}
			case 8: { // FreeImg uses GBRA or GBR; not sure what happens with 8 and 4 bit. cant GL_GB or GL_G respective
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, m_Width, m_Height, 0, GL_RG, GL_UNSIGNED_BYTE, pixels);
				break;
			}
			case 4: {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R, m_Width, m_Height, 0, GL_R, GL_UNSIGNED_BYTE, pixels);
				break;
			}
			}
			
			glBindTexture(GL_TEXTURE_2D, 0);

			
			delete[] pixels;

			return generatedTextureID;
		}

} }