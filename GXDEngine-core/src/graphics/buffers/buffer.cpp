// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma optimize( "f", on )

#include "../../stdafx.h"
#include "buffer.h"

namespace GXDEngine {
    namespace graphics {

        Buffer::Buffer(GLfloat *data, GLsizei count, GLuint componentCount) 
                : m_componentCount(componentCount) {

            glGenBuffers(1, &m_bufferID);
            glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
            glBufferData(GL_ARRAY_BUFFER, (size_t)count * sizeof(GLfloat), data, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        Buffer::~Buffer() {
            glDeleteBuffers(1, &m_bufferID);
        }


        void Buffer::bind() const  {
            glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        }

        void Buffer::unbind() const  {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }


    }
}