#include "MovementSystem.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"

MovementSystem::MovementSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<RigidbodyComponent>();
}

void MovementSystem::Update(double deltaTime)
{
    std::string ids = "";
    for (Entity entity : GetSystemEntities())
    {
        auto& transform = entity.GetComponent<TransformComponent>();
        const auto rigidbody = entity.GetComponent<RigidbodyComponent>();

        transform.location.x += rigidbody.velocity.x * deltaTime;
        transform.location.y += rigidbody.velocity.y * deltaTime;
        ids += std::to_string(entity.GetID()) + ", ";
    }

#ifdef DEBUG_SYSTEM
    if (ids != "")
        Logger::Info("Movement System on " + ids);
#endif
}