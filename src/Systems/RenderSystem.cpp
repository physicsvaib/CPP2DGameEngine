#include "RenderSystem.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include <SDL2/SDL_image.h>

RenderSystem::RenderSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<SpriteComponent>();
}

void RenderSystem::Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& AssetStore)
{

    for (auto entity : GetSystemEntities())
    {
        const auto transform = entity.GetComponent<TransformComponent>();
        const auto sprite = entity.GetComponent<SpriteComponent>();

        SDL_Rect rect{static_cast<int>(transform.location.x),
                      static_cast<int>(transform.location.y),
                      static_cast<int>(sprite.width * transform.scale.x),
                      static_cast<int>(sprite.height * transform.scale.y)};
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // SDL_RenderFillRect(renderer, &rect);
        SDL_RenderCopyEx(renderer, AssetStore->GetTexture(sprite.image), &sprite.srcRect, &rect,
                         transform.rotation, NULL, SDL_FLIP_NONE);
    }
}
