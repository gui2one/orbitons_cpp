#ifndef RESURCE_LIBRARY_H
#define RESURCE_LIBRARY_H

#include "pch.h"
#include "core.h"

#define RESOURCE_TYPE_NAME(type)                                                       \
    static ResourceItemType GetStaticType() { return ResourceItemType::type; }         \
    virtual ResourceItemType GetEventType() const override { return GetStaticType(); } \
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
        virtual ~ResourceItem(){};

        std::string path;
        virtual ResourceItemType GetEventType() const = 0;
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
        MeshItem() {}
        RESOURCE_TYPE_NAME(MeshItem)
    };

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
            items.push_back(item);
        }

    private:
        ResourceLibrary(){};
    };
} // namespace Orbitons
#endif /* RESURCE_LIBRARY_H */