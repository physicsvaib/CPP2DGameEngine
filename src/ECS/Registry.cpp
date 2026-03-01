#include "Registry.h"
#include "../Logger/Logger.h"

Entity Registry::CreateEntity()
{
    Entity new_entity{numEntities++};
    entitiesToBeAdded.insert(new_entity);

    Logger::Info("Created a new Entity with id " + std::to_string(numEntities));

    return new_entity;
}

void Registry::AddEntityToSystem(Entity newEntity) {}

void Registry::Update()
{
    for (Entity entity : entitiesToBeAdded)
    {
        AddEntityToSystem(entity);
    }

    entitiesToBeAdded.clear();
}
