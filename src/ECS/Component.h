#ifndef COMPONENT_H
#define COMPONENT_H

#include "Signature.h"

struct IComponent
{
  protected:
    static int nextID;
};

// int IComponent::nextID = 0;

template <typename TComponent> class Component : public IComponent
{
  public:
    static int GetID()
    {
        static const auto id = nextID++;
        return id;
    }
};

#endif