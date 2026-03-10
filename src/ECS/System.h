#ifndef SYSTEM_H
#define SYSTEM_H

#include "Component.h"
#include "Entity.h"
#include "Signature.h"
#include <vector>

// The system processes entities that contain a specific signature
class System
{
  public:
    System() = default;
    ~System() = default;

    virtual void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);

    const std::vector<Entity>& GetSystemEntities() const;
    const Signature& GetComponentSignature() const;

    template <typename TComponent> void RequireComponent();

  protected:
    Signature componentSignature;
    std::vector<Entity> entities;
};

template <typename TComponent> void System::RequireComponent()
{
    const auto componentID = Component<TComponent>::GetID();
    componentSignature.set(componentID);
}

#endif