// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "batchRenderer2D.h"

namespace GXDEngine { namespace graphics {
	
	std::vector<GLuint> BatchRenderer2D::m_TextureSlots;

	BatchRenderer2D::BatchRenderer2D()  {
		m_VAO = 0;
		m_VBO = 0;
		m_TextureSlots.reserve(32);
		init();
		m_IndexCount = 0;
	}

	BatchRenderer2D::~BatchRenderer2D() {
		delete m_IBO;
		glDeleteBuffers(1, &m_VBO);
	}

	

	void BatchRenderer2D::begin() {
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
#if _GXDE_ENABLE_DEBUG
		GLuint error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Bind Buffer Error: " << error << std::endl;
#endif
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#if _GXDE_ENABLE_DEBUG
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Map Buffer Error: " << error << std::endl;
#endif
	}

	void BatchRenderer2D::end() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
#if _GXDE_ENABLE_DEBUG
		GLuint error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "UnMap Buffer Error: " << error << std::endl;
#endif
		glBindBuffer(GL_ARRAY_BUFFER, 0);
#if _GXDE_ENABLE_DEBUG
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Unbind Buffer Error: " << error << std::endl;
#endif
	}

	void BatchRenderer2D::submit(const Renderable2D* renderable) {
		
		const maths::vec2& size = renderable->getSize();
		const maths::vec3& pos = renderable->getPosition();
		const unsigned int color = renderable->getColor();
		const std::vector<maths::vec2>& uv = renderable->getUV();
		const GLuint texID = renderable->getTID();

		float texSlot = 0.0f;
		if (texID) {

			bool found = false;
			const short sizeTS = (short)m_TextureSlots.size();
			for (int i = 0; i < sizeTS; ++i) {
				if (m_TextureSlots[i] == texID) {
					found = true;
					texSlot = (float)(i + 1);
					break;
				}
			}

			if (!found) {
				if (sizeTS >= 32) { //-V112
					end();
					flush();
					begin();
				}

				m_TextureSlots.push_back(texID);
				texSlot = (float)(sizeTS);

			}
		}

		m_Buffer->vertex = *m_TFBack * pos;
		m_Buffer->UV = uv[0];
		m_Buffer->textureID = texSlot;
		m_Buffer->color = color;
		++m_Buffer;

		m_Buffer->vertex = m_TFBack->multiply(pos.m_x, pos.m_y + size.m_y, pos.m_z);
		m_Buffer->UV = uv[1];
		m_Buffer->textureID = texSlot;
		m_Buffer->color = color;
		++m_Buffer;

		m_Buffer->vertex = m_TFBack->multiply(pos.m_x + size.m_x, pos.m_y + size.m_y, pos.m_z);
		m_Buffer->UV = uv[2];
		m_Buffer->textureID = texSlot;
		m_Buffer->color = color;
		++m_Buffer;

		m_Buffer->vertex = m_TFBack->multiply(pos.m_x + size.m_x, pos.m_y, pos.m_z);
		m_Buffer->UV = uv[3];
		m_Buffer->textureID = texSlot;
		m_Buffer->color = color;
		++m_Buffer;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::flush() {
#if _GXDE_ENABLE_DEBUG
		GLuint error;
#endif
		unsigned short sz = m_TextureSlots.size();
		for (int i = 0; i < sz; ++i)	{
			glActiveTexture(GL_TEXTURE0 + i);		
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
#if _GXDE_ENABLE_DEBUG
			error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "Bind Texture Error: " << error << "for Texture "<< i << std::endl;
#endif
		}

		glBindVertexArray(m_VAO);
		m_IBO->bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_IBO->unbind();
		glBindVertexArray(0);

		m_IndexCount = 0;

	}



	void BatchRenderer2D::init() {
		glGenVertexArrays(1, &m_VAO);
#if _GXDE_ENABLE_DEBUG
		GLuint error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Gen Vertex Array Error: " << error << std::endl;
#endif
		glGenBuffers(1, &m_VBO);
#if _GXDE_ENABLE_DEBUG
		error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "Gen Buffer m_VBO Error: " << error << std::endl;
#endif
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TEXID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::UV)));
		glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::textureID)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

		glBindVertexArray(0);

	}



	//void BatchRenderer2D::drawString(const std::string& str, const maths::vec3& position, Font& font, const unsigned int color) {
	void BatchRenderer2D::drawString(rapidstring& str, const maths::vec3& position, Font& font, const unsigned int color) {

		float texSlot = 0.0f;
		bool found = false;
		const short size = (short)m_TextureSlots.size();

		const unsigned int fontID = font.getID();

		for (int i = 0; i < size; ++i) {
			if (m_TextureSlots[i] == fontID) {
				found = true;
				texSlot = (float)(i + 1);
				break;
			}
		}
		if (!found) {
			if (size >= 32) {
				end();
				flush();
				begin();
			}

			m_TextureSlots.push_back(fontID);
			texSlot = (float)(size);
		}

		const float scaleX = 1366.0f / 32.0f;
		const float scaleY = 786.0f / 18.0f;

		float x = position.m_x;

		float kerning;
		int offset_x;
		int offset_y;
		unsigned long long width;
		unsigned long long height;
		float s0;
		float t0;
		float s1;
		float t1;
		float advance_x;
		
		size_t strLen = rs_len(&str);

		for (size_t i = 0; i < strLen ; ++i) {
			const char c = rs_data(&str)[i];

			font.getGlyphVaules(c, (int)i, rs_data(&str), kerning, offset_x, offset_y, width, height, s0, t0, s1, t1, advance_x);

			if (i > 0)
			{
				x += kerning / scaleX;
			}

			const float x0 = x + offset_x / scaleX;
			const float y0 = position.m_y + offset_y / scaleY;
			const float x1 = x0 + width  / scaleX;
			const float y1 = y0 - height / scaleY;
			
			const float u0 = s0;
			const float v0 = t0;
			const float u1 = s1;
			const float v1 = t1;

			//std::cout << "X,Y "<< x0 << ", " << y0 << std::endl;
			//std::cout << "U,V " << u0 << ", " << v0 << std::endl;

			m_Buffer->vertex = m_TFBack->multiply(x0, y0, 0);
			m_Buffer->UV = maths::vec2(u0, v0);
			m_Buffer->textureID = texSlot;
			m_Buffer->color = color;
			++m_Buffer;				
				
			m_Buffer->vertex = m_TFBack->multiply(x0, y1, 0);
			m_Buffer->UV = maths::vec2(u0, v1);
			m_Buffer->textureID = texSlot;
			m_Buffer->color = color;
			++m_Buffer;				
				
			m_Buffer->vertex = m_TFBack->multiply(x1, y1, 0);
			m_Buffer->UV = maths::vec2(u1, v1);
			m_Buffer->textureID = texSlot;
			m_Buffer->color = color;
			++m_Buffer;				
				
			m_Buffer->vertex = m_TFBack->multiply(x1, y0, 0);
			m_Buffer->UV = maths::vec2(u1, v0);
			m_Buffer->textureID = texSlot;
			m_Buffer->color = color;
			++m_Buffer;

			m_IndexCount += 6;
				
			x += advance_x / scaleX;
			

		}

		unsigned int status = GL_RED;
		switch (font.getDepth()) {
		case 4: {
			status = (unsigned int)GL_RGBA;
			break;
		}
		case 3: {
			status = GL_RGB;
			break;
		}
		case 2: {
			status = GL_LUMINANCE_ALPHA;
			break;
		}
		}

		glTexImage2D(GL_TEXTURE_2D, 0, status, font.getAtlasWidth(), font.getAtlasHeight(), 0, status, GL_UNSIGNED_BYTE, font.getAtlasData());
	}
} }