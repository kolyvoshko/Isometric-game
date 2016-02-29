/**
  * @file interactive_object.h
  */

#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include <list>
#include <SFML/Graphics.hpp>

//#include "object_manager.h"

enum class ObjectType { VOID, PLANT, ANIMAL, HERBIVORE, CARNIVORE};
enum class ActionType {VOID, EAT, ESCAPE, REPRODUCE};

struct UpdateMessage{
    ActionType actionType;

    // iteraction distance
    int i_number_of_plant;
    int i_number_of_carnivore;
    int i_number_of_herbivore;

    // visible distance
    int v_number_of_plant;
    int v_number_of_carnivore;
    int v_number_of_herbivore;
};


class InteractiveObject
{
public:
    ObjectType TYPE;
//    ObjectManager * objmanager;

    sf::CircleShape draw_object;

    virtual void update(const float dt) = 0;
    virtual void draw(sf::RenderWindow &window, const float dt) = 0;

//    virtual UpdateMessage send_message() = 0;
//    virtual void get_message(UpdateMessage message) = 0;
    virtual sf::Vector2f get_position() = 0;

    virtual ~InteractiveObject(){}
};

#endif // INTERACTIVEOBJECT_H
