#include "../../stdafx.h"
#pragma optimize( "f", on )

#include "vertexArray.h"

namespace GXDEngine {
    namespace graphics {

        VertexArray::VertexArray()  {
            glGenVertexArrays(1, &m_ArrayID);

        }

        VertexArray::~VertexArray() {
            for (int i = 0; i < m_Buffer.size(); ++i) {
                delete m_Buffer[i];
            }

            glDeleteVertexArrays(1, &m_ArrayID);
        }


        void VertexArray::addBuffer(Buffer *buffer, GLuint index) {
            bind();
            buffer->bind();

            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

            buffer->unbind();
            unbind();

            m_Buffer.push_back(buffer);
        }

        void VertexArray::bind() const  {
            glBindVertexArray(m_ArrayID);
        }

        void VertexArray::unbind() const  {
            glBindVertexArray(0);
        }
    }
}
