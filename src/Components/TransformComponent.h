#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../ECS/Component.h"
#include <glm/glm.hpp>

struct TransformComponent
{
    glm::vec2 location;
    glm::vec2 scale;
    double rotation;

    TransformComponent(glm::vec2 loc = glm::vec2(0, 0), glm::vec2 scale = glm::vec2(1, 1),
                       double rot = 0.0)
    {
        this->location = loc;
        this->rotation = rot;
        this->scale = scale;
    }
};

#endif