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
    ;
    bool operator<(const Entity& other) const
    {
        return GetID() < other.GetID();
    }

  private:
    int id;
};

#endif