#pragma once

class Entity;

class Component
{
public:
    Entity *owner;
    virtual ~Component() {}
    virtual void initialize() {}
    virtual void update(float t_deltaTime) {}
    virtual void render() {}
};
