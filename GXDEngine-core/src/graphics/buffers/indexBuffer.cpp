// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "indexBuffer.h"

namespace GXDEngine {
    namespace graphics {

        IndexBuffer::IndexBuffer(GLushort *data, GLsizei count) 
                : m_Count(count) {

            glGenBuffers(1, &m_bufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (size_t)count * sizeof(GLushort), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IndexBuffer::IndexBuffer(GLuint *data, GLsizei count) 
                : m_Count(count) {

            glGenBuffers(1, &m_bufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, (size_t)count * sizeof(GLuint), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        IndexBuffer::~IndexBuffer() {
            glDeleteBuffers(1, &m_bufferID);
        }


        void IndexBuffer::bind() const  {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
        }

        void IndexBuffer::unbind() const  {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }


    }
}