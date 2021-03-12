#include "FrameBuffer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
namespace Orbitons{
    Ref<FrameBuffer> FrameBuffer::create(){
        return MakeRef<OpenGLFrameBuffer>();
    }
}