#include "CollisionRenderSystem.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

#include "SDL2/SDL.h"

CollisionRenderSystem::CollisionRenderSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<BoxColliderComponent>();
}

void CollisionRenderSystem::Update(SDL_Renderer* renderer)
{

    // this is for rendering the collision box
    for (Entity entity : GetSystemEntities())
    {
        auto trans = entity.GetComponent<TransformComponent>();
        auto collider = entity.GetComponent<BoxColliderComponent>();
        SDL_Rect rect{static_cast<int>(trans.location.x + collider.offset.x),
                      static_cast<int>(trans.location.y + collider.offset.y), static_cast<int>(collider.size.x),
                      static_cast<int>(collider.size.y)};
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
}
