#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>

namespace Orbitons
{
    struct TransformComponent{

        glm::mat4 Transforms;

        TransformComponent() = default;
        TransformComponent(const TransformComponent& other) = default;
        TransformComponent(const glm::mat4& matrix)
            :Transforms(matrix)
            {

            }


    };
} // namespace Orbitons


#endif /*COMPONENTS_H*/