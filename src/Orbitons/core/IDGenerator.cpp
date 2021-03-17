#include "IDGenerator.h"
#include <chrono>

namespace Orbitons{

    bool IDGenerator::generateID(size_t* id){
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
        *id = (size_t)nanos;
        return true;
    }
}