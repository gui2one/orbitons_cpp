#include "Serializer.h"

namespace Orbitons
{
    Serializer::Serializer()
    {
        printf("Serializer constructor\n");
    }

    YAML::Node Serializer::serializeScene(Scene *scene)
    {

        YAML::Node root, entities;

        root["entities"] = entities;
        entities.begin();
        scene->m_registry.each([&](auto entity) {
            YAML::Node entity_node;
            Entity ent = Entity{entity, scene};

            if (ent.hasComponent<UUIDComponent>())
            {
                YAML::Node node;
                node["uuid"] = ent.getComponent<UUIDComponent>().uuid;
                entity_node["UUIDComponent"] = node;
            }
            if (ent.hasComponent<TagComponent>())
            {
                YAML::Node node;
                node["tagName"] = ent.getComponent<TagComponent>().tagName;
                entity_node["tagComponent"] = node;
                // printf("entity name : %s\n", ent.getComponent<TagComponent>().tagName.c_str());
            }

            if (ent.hasComponent<TransformComponent>())
            {
                YAML::Node node;
                auto &trans = ent.getComponent<TransformComponent>();
                node["position"] = trans.position;
                node["rotation"] = trans.rotation;
                node["scale"] = trans.scale;

                entity_node["transformComponent"] = node;
            }

            if (ent.hasComponent<MeshComponent>())
            {
                YAML::Node node;
                auto &comp = ent.getComponent<MeshComponent>();

                if (comp.mesh_item)
                {

                    node["meshItem"] = comp.mesh_item->getUUID();
                }

                entity_node["meshComponent"] = node;
            }

            entities.push_back(entity_node);
        });

        entities.end();
        return root;
    }

    YAML::Node Serializer::serializeResources(const ResourceLibrary &resources)
    {

        YAML::Node root, node;
        node.begin();
        for (auto &res : resources.items)
        {
            YAML::Node res_node;
            res_node["type"] = res->GetName();
            res_node["uuid"] = res->getUUID();
            res_node["path"] = res->path;
            node.push_back(res_node);
        }
        node.end();
        root["resources"] = node;
        return root;
    }
} // namespace Orbitons
