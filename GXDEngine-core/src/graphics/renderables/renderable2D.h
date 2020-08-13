#pragma once
#pragma optimize( "f", on )

#include "../shader.h"
#include "../renderers/renderer2D.h"
#include "../texture.h"

namespace GXDEngine { namespace graphics {

	struct VertexData{
		maths::vec3 vertex;
		maths::vec2 UV;
		float textureID;
		unsigned int color;
	};

	class Renderable2D {
	protected:
		maths::vec2 m_Size;
		maths::vec3 m_Pos;
		unsigned int m_Color;
		std::vector<maths::vec2> m_UV;
		Texture* m_Texture;

	protected:

		Renderable2D() { m_Color = 0; m_Texture = nullptr; initUV(); }

	public:
		Renderable2D(maths::vec3 position, maths::vec2 size, unsigned int color)
			: m_Pos(position), m_Size(size), m_Color(color) { m_Texture = nullptr; initUV(); }

		virtual ~Renderable2D() {}

		virtual void submit(Renderer2D* renderer) const { renderer->submit(this); }

		inline void setColor(unsigned int color)  { m_Color = color; }
		inline void setColor(const maths::vec4& color)  {
			const int r = (int)(color.m_x * 255.0f);
			const int g = (int)(color.m_y * 255.0f);
			const int b = (int)(color.m_z * 255.0f);
			const int a = (int)(color.m_w * 255.0f);

			m_Color = (a << 24 | b << 16 | g << 8 | r);
		}

		inline const maths::vec2& getSize() const  { return m_Size; }
		inline const maths::vec3& getPosition() const  { return m_Pos; }
		inline const unsigned int getColor() const  { return m_Color; }
		inline const std::vector<maths::vec2>& getUV() const  { return m_UV; }

		inline const GLuint getTID() const  { return m_Texture == nullptr ? 0 : m_Texture->getID(); }

	private:
		void initUV() {
			m_UV.emplace_back(maths::vec2(0, 0));
			m_UV.emplace_back(maths::vec2(0, 1));
			m_UV.emplace_back(maths::vec2(1, 1));
			m_UV.emplace_back(maths::vec2(1, 0));
		}
	};
} }