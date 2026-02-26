#ifndef SYSTEM_H
#define SYSTEM_H

#include "Entity.h"
#include "Signature.h"
#include <vector>

// The system processes entities that contain a specific signature
class System
{
  public:
    System() = default;
    ~System() = default;

    void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);

    const std::vector<Entity>& GetSystemEntities() const;
    const Signature& GetComponentSignature() const;

  private:
    Signature componentSignature;
    std::vector<Entity> entities;
};

#endif