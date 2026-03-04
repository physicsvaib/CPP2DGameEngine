#include "Registry.h"
#include "../Logger/Logger.h"

Entity Registry::CreateEntity()
{
    int currentIndex = numEntities++;
    Entity newEntity{currentIndex};
    newEntity.parent = this;
    entitiesToBeAdded.insert(newEntity);

    if (static_cast<uint>(numEntities) >= entityComponentSignature.size())
    {
        entityComponentSignature.resize(currentIndex + 1);
    }

    Logger::Info("Created a new Entity with id " + std::to_string(currentIndex));

    return newEntity;
}

#include "System.h"

void Registry::AddEntityToSystem(Entity newEntity)
{
    auto entityId{newEntity.GetID()};
    const Signature& signature = entityComponentSignature[entityId];

    for (auto system : systems)
    {
        bool isIntersted = (signature & system.second->GetComponentSignature()) ==
                           system.second->GetComponentSignature();
        Logger::Warning(std::to_string(isIntersted) + " for " +
                        system.second->GetComponentSignature().to_string() + " for " +
                        std::to_string(entityId) + " actual " + signature.to_string());

        if (isIntersted)
        {
            system.second->AddEntityToSystem(newEntity);
        }
    }
}

void Registry::Update()
{
    for (Entity entity : entitiesToBeAdded)
    {
        AddEntityToSystem(entity);
    }
    entitiesToBeAdded.clear();

    // for (Entity entity : entitiesToBeRemoved)
    // {
    //     Remove
    // }
}
