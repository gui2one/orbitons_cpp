#ifndef GRAPHIC_CONTEXT_H
#define GRAPHIC_CONTEXT_H

#include "core.h"
namespace Orbitons
{
    
    class GraphicContext{
    public:
        virtual ~GraphicContext() = default;

        virtual void init() = 0;
        virtual void swapBuffers() = 0;

        static std::unique_ptr<GraphicContext> create(void * window_ptr);
    private:

    };
} // namespace Oritons

#endif /* GRAPHIC_CONTEXT_H */