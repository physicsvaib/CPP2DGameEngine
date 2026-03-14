#include "System.h"
#include <algorithm>

void System::AddEntityToSystem(Entity entity)
{
    entities.push_back(entity);
    // lets just sort stuff here why on update
}

void System::RemoveEntityFromSystem(Entity entity)
{
    Logger::Info("Trying to remove " + std::to_string(entity.GetID()) + " " + componentSignature.to_string());
    entities.erase(
        std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) { return entity == other; }),
        entities.end());

    // entities.erase();
}

const std::vector<Entity>& System::GetSystemEntities() const
{
    return entities;
}

const Signature& System::GetComponentSignature() const
{
    return componentSignature;
}
