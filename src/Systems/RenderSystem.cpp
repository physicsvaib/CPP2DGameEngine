#include "RenderSystem.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include <SDL2/SDL_image.h>
#include <algorithm>

RenderSystem::RenderSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<SpriteComponent>();
}

void RenderSystem::Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& AssetStore)
{
    std::string ids;
    for (auto entity : GetSystemEntities())
    {
        const auto transform = entity.GetComponent<TransformComponent>();
        const auto sprite = entity.GetComponent<SpriteComponent>();

        SDL_Rect rect{static_cast<int>(transform.location.x), static_cast<int>(transform.location.y),
                      static_cast<int>(sprite.width * transform.scale.x),
                      static_cast<int>(sprite.height * transform.scale.y)};

        SDL_RenderCopyEx(renderer, AssetStore->GetTexture(sprite.image), &sprite.srcRect, &rect, transform.rotation,
                         NULL, SDL_FLIP_NONE);
        ids += std::to_string(entity.GetID()) + ", ";
    }

#ifdef DEBUG_SYSTEM
    if (ids != "")
        Logger::Info("Render System on " + ids);
#endif
}

void RenderSystem::AddEntityToSystem(Entity entity)
{
    System::AddEntityToSystem(entity);
    std::sort(entities.begin(), entities.end(), [](Entity& first, Entity& second)
              { return first.GetComponent<SpriteComponent>().zIndex < second.GetComponent<SpriteComponent>().zIndex; });
}
