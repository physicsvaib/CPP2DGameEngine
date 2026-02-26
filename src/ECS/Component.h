#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
  public:
    Component(int id) : comp_id(id) {}
    int GetCompId() const;

  private:
    int comp_id;
};

#endif