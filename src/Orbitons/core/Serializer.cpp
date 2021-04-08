#include "Serializer.h"

namespace Orbitons
{
    Serializer::Serializer()
    {
        // printf("Serializer constructor\n");
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
                else
                {
                    node["meshItem"] = "";
                }

                entity_node["meshComponent"] = node;
            }

            if (ent.hasComponent<CameraComponent>())
            {
                YAML::Node node;
                auto &comp = ent.getComponent<CameraComponent>();
                node["active"] = comp.active;
                node["angle"] = comp.angle;
                node["near"] = comp.near;
                node["far"] = comp.far;

                entity_node["cameraComponent"] = node;
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

    void Serializer::deserialize(const std::string &file_path, Scene *scene, ResourceLibrary &resources)
    {
        std::vector<YAML::Node> nodes = YAML::LoadAllFromFile(file_path);

        // clear all resources

        SelectionContext::getInstance().setSelectedEntity(Entity(entt::null, scene));
        SelectionContext::getInstance().m_selectedResource = nullptr;

        resources.items.clear();

        for (const auto entity : scene->m_registry.view<UUIDComponent>())
        {
            scene->m_registry.remove_all(entity);
            scene->m_registry.destroy(entity);
        }
        for (auto node : nodes)
        {
            if (node["resources"])
            {

                // found resources node
                for (auto &node : node["resources"])
                {
                    if (node["type"].as<std::string>() == std::string("MeshItem"))
                    {
                        Ref<MeshItem> item = MakeRef<MeshItem>(node["path"].as<std::string>());

                        resources.addItem(item);

                        // set UUID AFTER adding to resource library to override UUID as it is set in addItem method
                        item->setUUID(node["uuid"].as<std::string>());
                        ///////////////
                    }
                }
            }
        }

        for (auto node : nodes)
        {

            if (node["entities"])
            {
                // found entities node

                for (auto &entt_node : node["entities"])
                {
                    std::string name = "";
                    if (entt_node["tagComponent"])
                    {
                        name = entt_node["tagComponent"]["tagName"].as<std::string>();
                    }
                    Entity &entity = scene->createEntity(name);

                    if (entt_node["UUIDComponent"])
                    {
                        std::string uuid = "";
                        uuid = entt_node["UUIDComponent"]["uuid"].as<std::string>();

                        entity.getComponent<UUIDComponent>().uuid = uuid;
                    }

                    if (entt_node["transformComponent"])
                    {
                        glm::vec3 position, rotation, scale;
                        position = entt_node["transformComponent"]["position"].as<glm::vec3>();
                        rotation = entt_node["transformComponent"]["rotation"].as<glm::vec3>();
                        scale = entt_node["transformComponent"]["scale"].as<glm::vec3>();

                        if (!entity.hasComponent<TransformComponent>())
                        {
                            scene->m_registry.emplace<TransformComponent>(entity, position);
                        }
                        entity.getComponent<TransformComponent>().position = position;
                        entity.getComponent<TransformComponent>().rotation = rotation;
                        entity.getComponent<TransformComponent>().scale = scale;
                    }

                    if (entt_node["meshComponent"])
                    {
                        std::string item_uuid = entt_node["meshComponent"]["meshItem"].as<std::string>();

                        // printf("item uui : %s\n", item_uuid.c_str());

                        if (!item_uuid.empty())
                        {
                            Ref<ResourceItem> res_item = nullptr;
                            res_item = ResourceLibrary::getInstance().getItemByUUID(item_uuid);

                            if (!entity.hasComponent<MeshComponent>())
                            {
                                printf("adding MeshComponent beacuse it's missing\n");
                                scene->m_registry.emplace<MeshComponent>(entity);
                            }

                            entity.getComponent<MeshComponent>().mesh_item = std::dynamic_pointer_cast<MeshItem>(res_item);
                        }
                    }

                    if (entt_node["cameraComponent"])
                    {

                        if (!entity.hasComponent<CameraComponent>())
                        {
                            scene->m_registry.emplace<CameraComponent>(entity);
                        }

                        entity.getComponent<CameraComponent>().active = entt_node["cameraComponent"]["active"].as<bool>();
                        entity.getComponent<CameraComponent>().angle = entt_node["cameraComponent"]["angle"].as<float>();
                        entity.getComponent<CameraComponent>().near = entt_node["cameraComponent"]["near"].as<float>();
                        entity.getComponent<CameraComponent>().far = entt_node["cameraComponent"]["far"].as<float>();
                    }
                }
            }
        }
    }
} // namespace Orbitons
