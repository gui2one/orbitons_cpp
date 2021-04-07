#ifndef RESURCE_LIBRARY_H
#define RESURCE_LIBRARY_H

#include "pch.h"
#include "core.h"
#include "Core/Mesh.h"
#include "Core/ObjectLoader.h"
#include "Core/IDGenerator.h"

#define RESOURCE_TYPE_NAME(type)                                                      \
    static ResourceItemType GetStaticType() { return ResourceItemType::type; }        \
    virtual ResourceItemType GetItemType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; }
namespace Orbitons
{

    enum class ResourceItemType
    {
        None = 0,
        TextureItem,
        MeshItem,
        MaterialItem
    };

    class ResourceItem
    {
    public:
        std::string path;
        std::string uuid;

    public:
        virtual ~ResourceItem(){};

        void setUUID(std::string generated) { uuid = generated; }
        const std::string getUUID() const { return uuid; }

        virtual ResourceItemType GetItemType() const = 0;
        virtual const char *GetName() const = 0;
    };

    class TextureItem : public ResourceItem
    {
    public:
        unsigned int width;
        unsigned int height;

        RESOURCE_TYPE_NAME(TextureItem)
    };

    class MeshItem : public ResourceItem
    {
    public:
        Mesh mesh;
        MeshItem() {}
        MeshItem(std::string file_path)
        {
            ObjLoader loader;
            path = file_path;
            mesh = loader.assimp_load(path);
        }
        RESOURCE_TYPE_NAME(MeshItem)
    };

    /*
        resource library
    */
    class ResourceLibrary
    {
    public:
        std::vector<Ref<ResourceItem>> items;

    public:
        static ResourceLibrary &getInstance()
        {

            static ResourceLibrary s_instance;

            return s_instance;
        }
        // prevent copy
        ResourceLibrary(const ResourceLibrary &other) = delete;
        void operator=(const ResourceLibrary &other) = delete;

        void addItem(Ref<ResourceItem> item)
        {
            item->setUUID(IDGenerator::generateUUID());
            items.push_back(item);
        }

        Ref<ResourceItem> getItemByUUID(std::string uuid)
        {

            auto it = std::find_if(items.begin(), items.end(), [&uuid](const Ref<ResourceItem> item) { return item->getUUID() == uuid; });
            if (it != items.end())
            {
                // found element. it is an iterator to the first matching element.
                // if you really need the index, you can also get it:
                auto index = std::distance(items.begin(), it);

                return items[index];
            }

            return nullptr;
        }

    private:
        ResourceLibrary(){};
    };
} // namespace Orbitons
#endif /* RESURCE_LIBRARY_H */