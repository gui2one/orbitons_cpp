#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "pch.h"
#include "yaml-cpp/yaml.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"

namespace YAML
{
    template <>
    struct convert<glm::vec3>
    {

        static Node encode(const glm::vec3 &vec)
        {
            Node node;
            node.SetStyle(EmitterStyle::Flow);
            node.push_back(vec.x);
            node.push_back(vec.y);
            node.push_back(vec.z);

            return node;
        }

        static bool decode(const Node &node, glm::vec3 &vec)
        {
            if (!node.IsSequence() || node.size() != 3)
            {
                return false;
            }

            vec.x = node[0].as<float>();
            vec.y = node[1].as<float>();
            vec.z = node[2].as<float>();

            return true;
        }
    };

    template <>
    struct convert<Orbitons::Entity>
    {

        static Node encode(Orbitons::Entity &entity)
        {

            Node node;
            auto &tag = entity.getComponent<Orbitons::TagComponent>();
            node["tag"] = tag.tagName;
            return node;
        }

        static bool decode(const Node &node, Orbitons::Entity &entity)
        {
            return true;
        }
    };
}

namespace Orbitons
{

    class Serializer
    {
    public:
        Serializer();

        YAML::Node serializeScene(Scene *scene);
        YAML::Node serializeResources(const ResourceLibrary &resources);

    private:
    };
} // namespace Orbitons
#endif /* SERIALIZER_H */