#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
  public:
    Entity(int id) : id(id) {}
    int GetID() const;

    bool operator==(const Entity& other) const
    {
        return other.GetID() == this->GetID();
    }

    Entity& operator=(const Entity& other) = default;

    bool operator<(const Entity& other) const
    {
        return GetID() < other.GetID();
    }

    class Registry* parent;

    template <typename TComponent, typename... TArgs> void AddComponent(TArgs... args);
    template <typename TComponent> void RemoveComponent();
    template <typename TComponent> bool HasComponent();
    template <typename TComponent> TComponent& GetComponent();
    void Kill();

  private:
    int id;
};

#include "Registry.h"

template <typename TComponent, typename... TArgs> void Entity::AddComponent(TArgs... args)
{
    parent->template AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent> void Entity::RemoveComponent()
{
    parent->template RemoveComponent<TComponent>(*this);
}

template <typename TComponent> bool Entity::HasComponent()
{
    return parent->template HasComponenet<TComponent>(*this);
}

template <typename TComponent> TComponent& Entity::GetComponent()
{
    return parent->template GetComponent<TComponent>(*this);
}

#endif