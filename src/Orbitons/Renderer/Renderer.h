#ifndef RENDERER_H
#define RENDERER_H

#include "pch.h"


namespace Orbitons
{

    enum class RenderAPI{
        None = 0,
        OpenGL = 1
    };

    class Renderer{
    public:

        inline static void init(){


            if(Renderer::getAPI() == RenderAPI::OpenGL){
                printf("OpenGL API was chosen\n");
            }

        }
        inline static void setAPI(const RenderAPI& api){
            s_renderAPI = api;

        }
        inline static RenderAPI getAPI(){
            return s_renderAPI;
        }
    private:
    static RenderAPI s_renderAPI;  

    };
    
} // namespace Orbitons
#endif /* RENDERER_H */