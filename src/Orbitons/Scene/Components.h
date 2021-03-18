#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
// #include "Core/Mesh.h"
#include "Scene/MeshObject.h"
#include "Renderer/Material.h"

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

        /* does not work as expected ... */
        // operator glm::mat4() { return transforms; }
    };

    struct MeshComponent
    {
        Ref<MeshObject> mesh_object;
        Ref<Material> material;

        MeshComponent() = default;
        MeshComponent(const MeshComponent &other) = default;
        MeshComponent(const Ref<MeshObject> &_mesh)
            : mesh_object(_mesh)
        {
            material = MakeRef<PhongMaterial>();

            // material->setDiffuseColor(glm::vec3(1.0f, 0.f, 0.f));
        }
    };

} // namespace Orbitons

#endif /* COMPONENTS_H  */