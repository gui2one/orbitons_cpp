#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

#include "pch.h"

#include "boost/lexical_cast.hpp"
#include "boost/uuid/random_generator.hpp"
#include "boost/uuid/uuid_io.hpp"
namespace Orbitons::IDGenerator
{

    bool generateID(size_t *id);
    std::string generateUUID();
}

#endif /*ID_GENERATOR_H*/