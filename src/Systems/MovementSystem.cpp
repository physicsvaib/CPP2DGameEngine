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

    Logger::Info(std::to_string(GetSystemEntities().size()));
    for (Entity entity : GetSystemEntities())
    {
        Logger::Info(std::to_string(entity.GetID()));
        auto& transform = entity.GetComponent<TransformComponent>();
        const auto rigidbody = entity.GetComponent<RigidbodyComponent>();

        transform.location.x += rigidbody.velocity.x * deltaTime;
        transform.location.y += rigidbody.velocity.y * deltaTime;

        Logger::Info("Current Location: " + std::to_string(transform.location.x) + " " +
                     std::to_string(transform.location.y));
    }
}