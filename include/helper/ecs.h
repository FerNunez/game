#pragma once

#include <iostream>
#include <memory>
#include <vector>

// Forward declaration of Entity and Component classes
class Entity;
class Component;

// Component base class
class Component
{
public:
    // Constructor for Component takes a reference to the Entity it belongs to
    Component(Entity& entity)
      : entity_(entity)
    {
    }

    // Virtual destructor for Component
    virtual ~Component()
    {
    }

    // Getter for the Entity that this Component belongs to
    Entity& entity()
    {
        return entity_;
    }

private:
    Entity& entity_; // Reference to the Entity that this Component belongs to
};

// Entity class
class Entity
{
public:
    // Constructor for Entity takes an ID and a name
    Entity(int id, const std::string& name)
      : id_(id)
      , name_(name)
    {
    }

    // Getters for the ID and name of the Entity
    int id() const
    {
        return id_;
    }
    const std::string& name() const
    {
        return name_;
    }

    // Add a Component to this Entity
    void AddComponent(std::shared_ptr<Component> component)
    {
        components_.push_back(component);
    }

    // Get a Component of a specific type from this Entity
    template<typename T>
    T* GetComponent()
    {
        for (auto& component : components_)
        {
            T* typed_component = dynamic_cast<T*>(component.get());
            if (typed_component != nullptr)
            {
                return typed_component;
            }
        }
        return nullptr;
    }

private:
    int id_;                                             // ID of the Entity
    std::string name_;                                   // Name of the Entity
    std::vector<std::shared_ptr<Component>> components_; // Components belonging to this Entity
};

// System base class
class System
{
public:
    // Virtual destructor for System
    virtual ~System()
    {
    }

    // Update function for the System
    virtual void Update(double dt) = 0;
};
