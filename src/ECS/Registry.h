#ifndef REGISTRY_H
#define REGISTRY_H

#include "Pool.h"
#include "Signature.h"
#include "System.h"
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

  private:
    int numEntities = 0;

    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeRemoved;

    std::vector<IPool*> componentPools;
    std::vector<Signature> entityComponentSignature;
    std::unordered_map<std::type_index, System*> systems;
};

#endif

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
        componentPools[componentID] = new Pool<TComponent>();
    }

    Pool<TComponent>* pool = Pool<TComponent>(componentPools[componentID]);

    if (pool->GetSize() <= entityID)
    {
        pool->Resize(numEntities);
    }

    TComponent comp(std::forward<TArgs>(args)...);
    pool->Set(entityID, comp);

    entityComponentSignature[entityID].set(componentID);
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
