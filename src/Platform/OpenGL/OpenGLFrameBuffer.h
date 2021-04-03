#ifndef OPENGL_FRAME_BUFFER_H
#define OPENGL_FRAME_BUFFER_H
#include "Renderer/FrameBuffer.h"

#include "pch.h"

namespace Orbitons
{

    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer();
        virtual ~OpenGLFrameBuffer();

        virtual void bind() override;
        virtual void unbind() override;
        virtual void invalidate(uint32_t width, uint32_t height) override;

        virtual const uint32_t getWidth() const override { return m_width; };
        virtual const uint32_t getHeight() const override { return m_height; };
        virtual const uint32_t getID() const override { return m_id; };

        virtual void setWidth(uint32_t width) override { m_width = width; };
        virtual void setHeight(uint32_t height) override { m_height = height; };

    private:
        uint32_t m_id;
        uint32_t m_colorAttachment;
        uint32_t m_depthAttachment;

        uint32_t m_width;
        uint32_t m_height;
    };
}
#endif /* OPENGL_FRAME_BUFFER_H */