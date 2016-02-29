#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <list>
#include <vector>
#include <string>
#include <SFML/System.hpp>

#include "interactive_object.h"
#include "../world.h"

/**
  * Задачі:
  * 1. Створення об'єктів (Фабричний метод).
  * 2. Управління об'єктами методом обміну повідомленнями.
  * 3. Реалізація взаємодії об'єктів (посредник)
  */


struct Neigborhood
{
    std::list<std::vector<InteractiveObject *> > plant, herbivore, carbivore;
    std::list<std::vector<double> > dist_to_plant, dist_to_herbivore, dist_to_carbivore;
};

class ObjectManager
{
    std::list<InteractiveObject *> objects;
    Neigborhood interacNeigborhood;
    Neigborhood visibleNeigborhood;
    Neigborhood savePtrNeigborhood;

    World * world;

    void updateNeigborhood();

public:
    ObjectManager();

    void createObject(std::string objType, sf::Vector2f pos);
    void updateObjects();
};

#endif // OBJECTMANAGER_H
