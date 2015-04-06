#pragma once

#include "OpenGL.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>

template<GLenum BType>
class Buffer {
    friend class VertexArray;
protected:
    GLsizeiptr size;
    GLuint id;
public:
    typedef Buffer<BType> TBuffer;
    void *data;
    Buffer(GLsizeiptr size, GLenum usage, void *copy=NULL) : size(size), id(0), data(std::malloc(size)) {
        glGenBuffers(1, &id);
        glBindBuffer(BType, id);
        if (copy != NULL)
            std::memcpy(data, copy, size);
        glBufferData(BType, size, data, usage);
    }
    Buffer(TBuffer &&move) {
        id = move.id;
        move.id = 0;
        data = move.data;
        move.data = 0;
        size = move.size;
        move.size = 0;
    }
    ~Buffer() {
        glDeleteBuffers(1, &id);
        std::free(data);
    }
    TBuffer &operator=(TBuffer &&move) {
        if (this != &move) {
            this->~Buffer();
            id = move.id;
            move.id = 0;
            data = move.data;
            move.data = 0;
            size = move.size;
            move.size = 0;
        }
        return *this;
    }
    void activate() {
        glBindBuffer(BType, id);
    }
    static void deactivate() {
        glBindBuffer(BType, 0);
    }
    void update(GLintptr offset, GLsizeiptr size) {
        glBufferSubData(BType, offset, size, (char *)data + offset);
    }
    void update() {
        glBufferSubData(BType, 0, size, data);
    }
};

#ifndef _MSC_VER
extern template class Buffer<GL_ARRAY_BUFFER>;
extern template class Buffer<GL_ELEMENT_ARRAY_BUFFER>;
#endif

typedef Buffer<GL_ARRAY_BUFFER> ArrayBuffer;
typedef ArrayBuffer VertexBuffer;
typedef Buffer<GL_ELEMENT_ARRAY_BUFFER> ElementArrayBuffer;
typedef ElementArrayBuffer IndexBuffer;
