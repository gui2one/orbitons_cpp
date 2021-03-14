#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "core.h"
#include "pch.h"

namespace Orbitons{

    class FrameBuffer{
    public:
        virtual ~FrameBuffer() = default;

        static Ref<FrameBuffer> create();
        virtual void bind() = 0;
        virtual void unbind() = 0;
        virtual void invalidate(uint32_t width, uint32_t height) = 0;

        virtual const uint32_t getWidth() const = 0;
        virtual const uint32_t getHeight() const = 0;
        virtual const uint32_t getID() const = 0;


        virtual void setWidth(uint32_t width) = 0;
        virtual void setHeight(uint32_t height) = 0;                  
    private:

    };
}
#endif /* FRAME_BUFFER_H */