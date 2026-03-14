#include "Entity.h"

int Entity::GetID() const
{
    return id;
}

void Entity::Kill()
{
    // Check if the entity has a parent before calling KillEntity
    if (parent != nullptr)
    {
        parent->KillEntity(*this);
    }
}
