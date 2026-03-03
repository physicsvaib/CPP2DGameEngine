#ifndef REGISTRY_H
#define REGISTRY_H

#include "../Logger/Logger.h"
#include "Pool.h"
#include "Signature.h"
#include "System.h"
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

class Registry
{
  public:
    Registry() = default;

    Entity CreateEntity();
    void AddEntityToSystem(Entity newEntity);
    void Update();

    template <typename TComponent, typename... TArgs>
    void AddComponent(Entity entity, TArgs&&... args);
    template <typename TComponent> void RemoveComponent(Entity entity);
    template <typename TComponent> bool HasComponenet(Entity entity);

    template <typename TSystem, typename... TArgs> void AddSystem(TArgs&&... args);
    template <typename TSystem> void RemoveSystem();
    template <typename TSystem> bool HasSystem() const;
    template <typename TSystem> TSystem& GetSystem() const;

  private:
    int numEntities = 0;

    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeRemoved;

    std::vector<std::shared_ptr<IPool>> componentPools;
    std::vector<Signature> entityComponentSignature;
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
};

template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs&&... args)
{
    const auto componentID = Component<TComponent>::GetID();
    const auto entityID = entity.GetID();

    if (componentPools.size() <= componentID)
    {
        componentPools.resize(componentID + 1, nullptr);
    }

    if (!componentPools[componentID])
    {
        componentPools[componentID] = std::make_shared<Pool<TComponent>>();
    }

    auto pool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentID]);

    if (pool->GetSize() <= entityID)
    {
        pool->Resize(numEntities);
    }

    TComponent comp(std::forward<TArgs>(args)...);
    pool->Set(entityID, comp);

    entityComponentSignature[entityID].set(componentID);

    Logger::Info("Comp Added " + std::to_string(componentID) + " to entity " +
                 std::to_string(entityID));
}

template <typename TComponent> void Registry::RemoveComponent(Entity entity)
{
    const auto compID = Component<TComponent>::GetID();
    const auto entityID = entity.GetID();

    entityComponentSignature[entityID].set(compID, false);
}

template <typename TComponent> bool Registry::HasComponenet(Entity entity)
{
    const auto compID = Component<TComponent>::GetID();
    const auto entityID = entity.GetID();

    return entityComponentSignature[entityID].test(compID);
}

template <typename TSystem, typename... TArgs> void Registry::AddSystem(TArgs&&... args)
{
    std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    auto typeId = std::type_index(typeid(TSystem));
    systems.insert(std::make_pair(typeId, newSystem));
}

template <typename TSystem> void Registry::RemoveSystem()
{
    auto typeId = systems.find(std::type_index(typeid(TSystem)));
    if (typeId == systems.end())
        return;

    systems.erase(typeId);
}

template <typename TSystem> bool Registry::HasSystem() const
{
    auto typeId = std::type_index(typeid(TSystem));
    return systems.find(typeId) != systems.end();
}

template <typename TSystem> TSystem& Registry::GetSystem() const
{
    auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}

#endif