#pragma once
#pragma optimize( "f", on )

#include "../../stdafx.h"

namespace GXDEngine {
    namespace graphics {

        class Buffer {
        private:
            GLuint m_bufferID;
            GLuint m_componentCount;

        public:
            Buffer(GLfloat *data, GLsizei count, GLuint compnentCount);

            ~Buffer();

            void bind() const;

            void unbind() const;

            inline GLuint getComponentCount() const  { return m_componentCount; }
        };


    }
}