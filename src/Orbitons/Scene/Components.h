#ifndef COMPONENTS_H
#define COMPONENTS_H
// #include "pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Renderer/VertexArray.h"
#include "Scene/MeshObject.h"
#include "Scene/ResourceLibrary.h"
#include "Renderer/Material.h"

namespace Orbitons
{

    struct UUIDComponent
    {

        std::string uuid;

        UUIDComponent() = default;
        UUIDComponent(const UUIDComponent &other) = default;
        UUIDComponent(const std::string &_uuid)
            : uuid(_uuid)
        {
        }
    };
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

        glm::vec3 position = {0.0f, 0.0f, 0.0f};
        glm::vec3 rotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 scale = {1.0f, 1.0f, 1.0f};

        TransformComponent() = default;
        TransformComponent(const TransformComponent &other) = default;
        TransformComponent(const glm::vec3 &_position)
            : position(_position)
        {
        }

        glm::mat4 getTransforms()
        {
            glm::mat4 rot_matrix = glm::toMat4(glm::quat(glm::radians(rotation)));
            return glm::translate(glm::mat4(1.0f), position) * rot_matrix * glm::scale(glm::mat4(1.0f), scale);
        }

        /* does not work as expected ... */
        // operator glm::mat4() { return transforms; }
    };

    struct MeshComponent
    {

        Ref<Material> material;
        Ref<MeshItem> mesh_item = nullptr;

        // MeshComponent() = default;
        MeshComponent()
        {
            material = MakeRef<PhongMaterial>();

            // material->setDiffuseColor(glm::vec3(1.0f, 0.f, 0.f));
        }
        MeshComponent(const MeshComponent &other) = default;
    };

    struct CameraComponent
    {

        bool active = false;
        float angle;
        float near = 0.01f;
        float far = 100.0f;

        CameraComponent() = default;
        CameraComponent(const CameraComponent &other) = default;
        CameraComponent(float _angle, float _near = 0.01f, float _far = 100.0f)
            : angle(_angle), near(_near), far(_far)
        {
        }
    };
} // namespace Orbitons

#endif /* COMPONENTS_H  */