#include "Registry.h"
#include "../Logger/Logger.h"
#include "System.h"

Entity Registry::CreateEntity()
{
    int currentIndex = -1;
    if (freeIds.empty())
    {
        currentIndex = numEntities++;
    }
    else
    {
        currentIndex = freeIds.front();
        freeIds.pop_front();
    }

    Entity newEntity{currentIndex};
    newEntity.parent = this;
    entitiesToBeAdded.insert(newEntity);

    if (static_cast<uint>(numEntities) >= entityComponentSignature.size())
    {
        entityComponentSignature.resize(currentIndex + 1);
    }

    Logger::Log("Created a new Entity with id " + std::to_string(currentIndex));

    return newEntity;
}

void Registry::KillEntity(Entity entity)
{
    Logger::Info("About to kill " + std::to_string(entity.GetID()));
    entitiesToBeRemoved.insert(entity);
}

void Registry::AddEntityToSystem(Entity newEntity)
{
    auto entityId{newEntity.GetID()};
    const Signature& signature = entityComponentSignature[entityId];

    for (auto system : systems)
    {
        bool isIntersted =
            (signature & system.second->GetComponentSignature()) == system.second->GetComponentSignature();

        if (isIntersted)
        {
            system.second->AddEntityToSystem(newEntity);
        }
    }
}

void Registry::RemoveEntityFromSystem(Entity entity)
{
    for (auto system : systems)
    {
        system.second->RemoveEntityFromSystem(entity);
    }
}

void Registry::Update()
{
    AddtionOfEntities();
    RemovalOfEntities();
}

void Registry::RemovalOfEntities()
{
    for (Entity entity : entitiesToBeRemoved)
    {
        RemoveEntityFromSystem(entity);
        entityComponentSignature[entity.GetID()].reset();
        freeIds.push_back(entity.GetID());
        Logger::Info("Removing " + std::to_string(entity.GetID()));
    }
    entitiesToBeRemoved.clear();
}

void Registry::AddtionOfEntities()
{
    for (Entity entity : entitiesToBeAdded)
    {
        AddEntityToSystem(entity);
    }
    entitiesToBeAdded.clear();
}
