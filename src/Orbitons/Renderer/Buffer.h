#ifndef BUFFER_H
#define BUFFER_H
#include <pch.h>
#include "core.h"

enum class ShaderDataType{
    None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool 

};


static uint32_t ShaderDataTypeSize(ShaderDataType type){
    switch(type){
        case ShaderDataType::None : ORBITONS_ASSERT(false, "bad data type"); return 0;
        case ShaderDataType::Float  : return sizeof(float) * 1;
        case ShaderDataType::Float2 : return sizeof(float) * 2;
        case ShaderDataType::Float3 : return sizeof(float) * 3;
        case ShaderDataType::Float4 : return sizeof(float) * 4;

        case ShaderDataType::Int  : return sizeof(int) * 1;
        case ShaderDataType::Int2 : return sizeof(int) * 2;
        case ShaderDataType::Int3 : return sizeof(int) * 3;
        case ShaderDataType::Int4 : return sizeof(int) * 4;

        case ShaderDataType::Mat3 : return sizeof(float) * 3 * 3;
        case ShaderDataType::Mat4 : return sizeof(float) * 4 * 4;

        case ShaderDataType::Bool : return sizeof(bool);
    }

    ORBITONS_ASSERT(false, "unknown ShaderDataType");
    return 0;

    
}

struct BufferElement{

    std::string Name;
    ShaderDataType Type;
    size_t Offset;
    uint32_t Size;

    BufferElement(ShaderDataType type, std::string name)
        :Name(name), Type(type), Offset(0), Size(ShaderDataTypeSize(type))
    {

    }

    uint32_t getNumComponents() const
    {
        switch(Type){
            case ShaderDataType::Float  : return 1;
            case ShaderDataType::Float2 : return 2;
            case ShaderDataType::Float3 : return 3;
            case ShaderDataType::Float4 : return 4;
            case ShaderDataType::Int    : return 1;
            case ShaderDataType::Int2   : return 2;
            case ShaderDataType::Int3   : return 3;
            case ShaderDataType::Int4   : return 4;
            case ShaderDataType::Mat3 : return 3;
            case ShaderDataType::Mat4 : return 4;
            case ShaderDataType::Bool : return 1;
        }

        ORBITONS_ASSERT(false, "unknown ShaderDataType");
        return 0;
    }

};

class BufferLayout{

public:
    BufferLayout (){};
    BufferLayout(std::initializer_list<BufferElement> elements)
        :m_elements(elements), m_stride(0)
    {
        computeOffsetAndStride();    
    }



    void computeOffsetAndStride(){

        m_stride = 0;
        size_t offset = 0;
        for(auto& element : m_elements){
            

            element.Offset = offset;
            offset += element.Size;
            m_stride += element.Size;

        }
        // printf("Layout stride : %d\n", m_stride);
        // ORBITONS_ASSERT(false, "Breaking Loop");

    }

    std::vector<BufferElement> getElements(){ return m_elements; }
    uint_fast16_t getStride(){ return m_stride; }

    // iterators
    std::vector<BufferElement>::iterator begin(){ return  m_elements.begin(); }
    std::vector<BufferElement>::iterator end(){ return  m_elements.end(); }

    std::vector<BufferElement>::const_iterator begin() const { return  m_elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return  m_elements.end(); }
private:
    std::vector<BufferElement> m_elements;

    uint32_t m_offset;
    uint32_t m_stride = 0;
};

class VertexBuffer{

public :
    virtual ~VertexBuffer(){};

    virtual void bind()  = 0;
    virtual void unbind()  = 0;
    virtual uint32_t getID()  = 0;
    virtual void setLayout(const BufferLayout& layout) = 0;
    virtual BufferLayout& getLayout() = 0; 
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