#ifndef GRAPHIC_CONTEXT_H
#define GRAPHIC_CONTEXT_H

#include "core.h"
namespace Orbitons
{
    
    class GraphicContext{
    public:
        virtual ~GraphicContext() = default;
        static std::unique_ptr<GraphicContext> create(void * window_ptr);

        virtual void init() = 0;
        virtual void swapBuffers() = 0;
        virtual const char* getVersion() = 0;
        virtual const char* getShadingLanguageVersion() = 0;
        
    private:

    };
} // namespace Oritons

#endif /* GRAPHIC_CONTEXT_H */