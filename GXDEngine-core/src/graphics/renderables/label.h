#pragma once
#pragma optimize( "f", on )

#include "renderable2D.h"
#include "../layers/layer.h"

namespace GXDEngine { namespace graphics {

		class Label : public Renderable2D {

		private:
			std::string m_String;
			Font* m_Font;

		public:
			Label(const float x, const float y, const unsigned int color, Font* font, const std::string text);
			void submit(Renderer2D* renderer) const override;

			void setText(const std::string text);
			inline const std::string& getText()  { return m_String; }
			void setPosition(const float x, const float y );

			const maths::vec3& getPosition() const;		
		};

} }