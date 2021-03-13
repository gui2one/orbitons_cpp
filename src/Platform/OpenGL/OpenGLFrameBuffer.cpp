#include "OpenGLFrameBuffer.h"

namespace Orbitons
{
    OpenGLFrameBuffer::OpenGLFrameBuffer(){
        invalidate(400,400);
    }

    void OpenGLFrameBuffer::invalidate(uint32_t width, uint32_t height){

        if(m_id){
            glDeleteFramebuffers(1, &m_id);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            glDeleteTextures(1, &m_colorAttachment);
            glBindTexture(GL_TEXTURE_2D, 0);

            printf("deleted frame buffer data\n");
        }

        if( width < 16) width = 16;
        if( height < 16) height = 16;

        glGenFramebuffers(1 , &m_id);

        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

        if( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
            ORBITONS_ASSERT(false, "problem with frame buffer");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::bind(){
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }
    void OpenGLFrameBuffer::unbind(){
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
} // namespace Orbitons
