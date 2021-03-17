#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
#include "Core/Mesh.h"

namespace Orbitons
{

    struct TagComponent
    {

        std::string tagName;

        TagComponent() = default;
        TagComponent(const TagComponent &other) = default;
        TagComponent(const std::string &name)
            : tagName(name)
        {
        }
    };

    struct TransformComponent
    {

        glm::mat4 transforms;

        TransformComponent() = default;
        TransformComponent(const TransformComponent &other) = default;
        TransformComponent(const glm::mat4 &matrix)
            : transforms(matrix)
        {
        }
    };

    struct MeshComponent
    {
        Mesh mesh;

        MeshComponent() = default;
        MeshComponent(const MeshComponent &other) = default;
        MeshComponent(const Mesh &_mesh)
            : mesh(_mesh)
        {
        }
    };
} // namespace Orbitons

#endif /*COMPONENTS_H*/