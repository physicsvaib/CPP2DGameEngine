#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
  public:
    Entity(int id) : id(id) {}
    int GetID() const;

  private:
    int id;
};

#endif