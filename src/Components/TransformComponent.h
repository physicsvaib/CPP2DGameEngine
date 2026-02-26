#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../ECS/Component.h"
#include <glm/glm.hpp>

struct TransformComponent : public Component
{
    glm::vec2 location;
    glm::vec2 scale;
    double rotation;
};

#endif