#pragma once
#pragma optimize( "f", on )

#include "../stdafx.h"


namespace GXDEngine { namespace graphics {
	
	class Texture {
	private:
		std::string m_Path;
		GLuint m_TextureID;
		GLsizei m_Width, m_Height;

	public:
		Texture(const std::string& path);
		~Texture();

		void bind() const;
		void unbind() const;

		inline unsigned int getWidth()  { return m_Width; }
		inline const unsigned int getHeight() const  { return m_Height; }
		inline const GLuint getID() const  { return m_TextureID; }

	private:
		GLuint load();

	};

} }