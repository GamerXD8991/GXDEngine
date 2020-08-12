#pragma once

#include "../../stdafx.h"

namespace GXDEngine {
    namespace graphics {
        class VertexArray {
        private:
            GLuint m_ArrayID;
            std::vector<Buffer *> m_Buffer;

        public:
            VertexArray();

            ~VertexArray();

            void addBuffer(Buffer *buffer, GLuint index);

            void bind() const;

            void unbind() const;

        };
    }
}




