#ifndef POOL_H
#define POOL_H

#include <vector>

class IPool
{
  public:
    virtual ~IPool() {};
};

template <typename TComponent> class Pool : public IPool
{
  public:
    Pool(int size = 100)
    {
        data.resize(size);
    }

    virtual ~Pool() = default;

    bool IsEmpty() const
    {
        return data.empty();
    }

    int GetSize() const
    {
        return data.size();
    }

    void Resize(int newSize)
    {
        data.resize(newSize);
    }

    void Clear()
    {
        data.clear();
    }

    void Add(TComponent comp)
    {
        data.push_back(comp);
    }

    void Set(int index, TComponent comp)
    {
        data[index] = comp;
    }

    TComponent& Get(int index) const
    {
        return static_cast<TComponent&>(data[index]);
    }

    TComponent& operator[](unsigned int index) const
    {
        return data[index];
    }

  private:
    std::vector<TComponent> data;
};

#endif