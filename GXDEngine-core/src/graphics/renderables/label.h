#pragma once
#pragma optimize( "f", on )

#include "renderable2D.h"
#include "../layers/layer.h"

namespace GXDEngine { namespace graphics {

		class Label : public Renderable2D {

		private:
			char* m_String;
			int m_StrLen;
			Font* m_Font;

		public:
			Label(const float x, const float y, const unsigned int color, Font* font, const char* text);
			void submit(Renderer2D* renderer) const override;

			void setText(const char* text);
			inline const std::string& getText()  { return m_String; }
			void setPosition(const float x, const float y );

			const maths::vec3& getPosition() const;		
		};

} }