#include "FrameBuffer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
namespace Orbitons
{
    FrameBuffer *FrameBuffer::create()
    {
        return new OpenGLFrameBuffer();
    }
}