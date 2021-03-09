#ifndef VERTEX_ARRAY_BUFFER_H
#define VERTEX_ARRAY_BUFFER_H

class VertexArrayBuffer{
public:

    virtual ~VertexArrayBuffer(){};

    virtual void bind() = 0;
    virtual void unbind() = 0;

    static VertexArrayBuffer* create();
private:

};
#endif /* VERTEX_ARRAY_BUFFER_H */