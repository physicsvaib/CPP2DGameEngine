#include "CollisionSystem.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

#include "SDL2/SDL.h"

CollisionSystem::CollisionSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<BoxColliderComponent>();
}

bool AreEntitiesColliding(Entity& ent1, Entity& ent2)
{
    auto trans1 = ent1.GetComponent<TransformComponent>();
    auto collider1 = ent1.GetComponent<BoxColliderComponent>();

    auto trans2 = ent2.GetComponent<TransformComponent>();
    auto collider2 = ent2.GetComponent<BoxColliderComponent>();

    // X Axis
    bool alignOnX =
        (trans1.location.x + collider1.offset.x < trans2.location.x + collider2.offset.x + collider2.size.x) &&
        trans1.location.x + collider1.offset.x + collider1.size.x > trans2.location.x + collider2.offset.x;

    bool alignOnY =
        (trans1.location.y + collider1.offset.y < trans2.location.y + collider2.offset.y + collider2.size.y) &&
        trans1.location.y + collider1.offset.y + collider1.size.y > trans2.location.y + collider2.offset.y;

    return alignOnX && alignOnY;
}

void CollisionSystem::Update()
{
    std::string ids = "";
    auto toLoopEntities = GetSystemEntities();
    for (auto it = toLoopEntities.begin(); it != toLoopEntities.end(); it++)
    {
        for (auto otherIt = it + 1; otherIt != toLoopEntities.end(); otherIt++)
        {
            bool areColliding = AreEntitiesColliding(*it, *otherIt);
            if (areColliding)
            {
                Logger::Info(std::to_string(it->GetID()) + " is colliding with " + std::to_string(otherIt->GetID()));
                it->Kill();
                otherIt->Kill();
            }
        }
        ids += std::to_string(it->GetID()) + ", ";
    }

#ifdef DEBUG_SYSTEM
    Logger::Info("Collision System on " + ids);
#endif
}
