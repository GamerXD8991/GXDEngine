#pragma once
#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "renderable2D.h"
#include "../layers/layer.h"

namespace GXDEngine { namespace graphics {

		class Label : public Renderable2D {

		private:
			//std::string m_String;
			rapidstring m_String;
			Font* m_Font;

		public:
			/*
			Label(const float x, const float y, const unsigned int color, Font* font, const std::string& text);
			Label(const float x, const float y, const unsigned int color, const std::string& font, const std::string& text);
			Label(const float x, const float y, const unsigned int color, const std::string& font, const unsigned int size, const std::string& text);
			inline void submit(Renderer2D* renderer) const { renderer->drawString(m_String, m_Pos, *m_Font, m_Color); };
			*/

			Label(const float x, const float y, const unsigned int color, Font* font, const rapidstring& text);
			Label(const float x, const float y, const unsigned int color, const std::string& font, const rapidstring& text);
			Label(const float x, const float y, const unsigned int color, const std::string& font, const unsigned int size, const rapidstring& text);
			void submit(Renderer2D* renderer) const { renderer->drawString(m_String, m_Pos, *m_Font, m_Color); };

			//void setText(const std::string& text);
			void setText(const rapidstring& text);
			//inline const std::string& getText()  { return m_String; }
			inline const rapidstring& getText()  { return m_String; }
			void setPosition(const float x, const float y );

			const maths::vec3& getPosition() const;		
		};

} }