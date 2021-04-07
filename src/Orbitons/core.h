#ifndef CORE_H
#define CORE_H

#include <memory>
#include <csignal>

/// define system Platform
#define ORBITONS_PLATFORM_WINDOWS

#ifdef ORBITONS_PLATFORM_WINDOWS
#include <windows.h>
#undef near
#undef far
#include <commdlg.h>
#include "psapi.h"
#endif /*ORBITONS_PLATFORM_WINDOWS*/

#include <string>

#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define BIND_EVENT_FUNCTION(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#ifdef _WIN32
#define HALT() std::raise(SIGINT);
#else
#define HALT() std::raise(SIGTRAP)
#endif
#define ORBITONS_ASSERT(x, message)                                                                            \
    if (!(x))                                                                                                  \
    {                                                                                                          \
        printf("Assertion Failed : \n--> %s \n    file : %s\n    line : %d\n\n", message, __FILE__, __LINE__); \
        HALT();                                                                                                \
    }

#define BIT(x) (1 << x)

#define ORBITONS_RES_DIR "../../resources"
/**
 * Base namespace for the whole application 
 * 
 */
namespace Orbitons
{

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Ref<T> MakeRef(Args &&...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}

#endif /*CORE_H*/