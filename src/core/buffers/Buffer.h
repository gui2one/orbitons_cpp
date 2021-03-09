#ifndef BUFFER_H
#define BUFFER_H
#include <pch.h>

enum class ShaderDataType{
    None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool 

};
struct BufferElement{

    std::string Name;
    ShaderDataType Type;

    BufferElement(ShaderDataType type, std::string name)
        :Name(name), Type(type)
    {

    }

};

class BufferLayout{

public:
    BufferLayout (){};
    BufferLayout(std::initializer_list<BufferElement> elements){
        m_elements = elements;
    }

    std::vector<BufferElement>::iterator begin(){ return  m_elements.begin(); }
    std::vector<BufferElement>::iterator end(){ return  m_elements.end(); }
private:
    std::vector<BufferElement> m_elements;
};

class VertexBuffer{

public :
    virtual ~VertexBuffer(){};

    virtual void bind()  = 0;
    virtual void unbind()  = 0;
    virtual uint32_t getID()  = 0;
    static VertexBuffer* create(float* vertices, uint32_t size);

};

class IndexBuffer{
public:
    virtual ~IndexBuffer(){};

    virtual void bind()  = 0;
    virtual void unbind()  = 0;    
    virtual uint32_t getID()  = 0;
    static IndexBuffer* create(uint32_t* indices, uint32_t size);
};

#endif /*BUFFER_H*/