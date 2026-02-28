#ifndef REGISTRY_H
#define REGISTRY_H

#include "Pool.h"
#include <vector>

class Registry
{
  public:
    Registry(int size = 100) {}

  private:
    std::vector<IPool*> componentPools;
};

#endif