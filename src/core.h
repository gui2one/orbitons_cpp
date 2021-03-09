#ifndef CORE_H
#define CORE_H


#include <memory>
#include <csignal>


#ifdef _WIN32
    #define HALT() std::raise(SIGINT);
#else
    #define HALT() std::raise(SIGTRAP)
#endif
#define ORBITONS_ASSERT(x, message)\
    if(!(x)){\
        printf("Assertion Failed : \n--> %s \n    file : %s\n    line : %d\n\n", message, __FILE__, __LINE__);\
        HALT();\
    }

// cosmetic only ??
namespace Orbitons{
    template<typename T>
    using Ref = std::shared_ptr<T>;
    
    template<typename T, typename ... Args>
    Ref<T> MakeRef(Args&& ... args){

        return std::make_shared<T>(std::forward<Args>(args)...);
    }

};

#endif /*CORE_H*/