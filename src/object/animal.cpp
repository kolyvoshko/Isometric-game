/**
  * @file animal.cpp
  */

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "animal.h"

Animal::Animal(AnimalGeneticCode genetic_code, sf::Vector2f coordinate)
{
    this->TYPE = ObjectType::ANIMAL;

    this->bellyful = ut::WindowValue(0.0, 1.0);
    this->bellyful.set(1.0);

    this->is_life = true;
    this->time_life = 0;
    this->last_reproduction = 0;

    this->genetic_code = genetic_code;
    this->coordinate = coordinate;

    this->max_width        = this->genetic_code.max_length;
    this->max_length       = this->genetic_code.max_width;

    this->max_eyesight     = this->genetic_code.max_eyesight;
    this->max_time_life    = this->genetic_code.max_time_life;
    this->max_turn         = this->genetic_code.max_turn;
    this->max_velosity     = this->genetic_code.max_velosity;
    this->max_acceleration = this->genetic_code.max_acceleration;
    this->max_mass         = this->genetic_code.max_mass;

    this->mass = 0.05 * max_mass;

    float vx, vy;

    vx = 2*((float)rand() / RAND_MAX) - 1;
    vy = 2*((float)rand() / RAND_MAX) - 1;

    vx *= this->max_velosity;
    vy *= this->max_velosity;

    this->velosity.x = vx;
    this->velosity.y = vy;
}

void Animal::find_neighborhood_object(std::list<InteractiveObject *> *obfects)
{
    return;
}

/// Implemented
bool Animal::is_live()
{
    return this->is_life;
}

/// Implemented
void Animal::find_animal(std::shared_ptr<Animal> al_ptr)
{
    sf::Vector2f al_coord = (al_ptr.get())->get_position();
    double l_distane_to_animal = ut::compute_dist(this->coordinate, al_coord);

    double l_iteraction_distance = 0.1;
    if (l_distane_to_animal < l_iteraction_distance){
        if ((al_ptr.get())->TYPE == ObjectType::CARNIVORE){
            list_iteraction_objects_ptr.predators.push_front(al_ptr);
            list_iteraction_objects_ptr.distance_to_predators.push_front(l_distane_to_animal);
        }

        else if((al_ptr.get())->TYPE == ObjectType::HERBIVORE)
        {
            list_iteraction_objects_ptr.herbivores.push_front(al_ptr);
            list_iteraction_objects_ptr.distance_to_herbivores.push_front(l_distane_to_animal);
        }
    }

    double l_visible_distance = this->eyesight;
    if (l_distane_to_animal < l_visible_distance){
        if ((al_ptr.get())->TYPE == ObjectType::CARNIVORE){
            list_visible_object_ptr.predators.push_front(al_ptr);
            list_visible_object_ptr.distance_to_predators.push_front(l_distane_to_animal);
        }

        else if((al_ptr.get())->TYPE == ObjectType::HERBIVORE)
        {
            list_visible_object_ptr.herbivores.push_front(al_ptr);
            list_visible_object_ptr.distance_to_herbivores.push_front(l_distane_to_animal);
        }
    }

    double l_save_object_distance = 10.0;
    if (l_distane_to_animal < l_save_object_distance){
        if ((al_ptr.get())->TYPE == ObjectType::CARNIVORE){
            list_save_object_ptr.predators.push_front(al_ptr);
            list_save_object_ptr.distance_to_predators.push_front(l_distane_to_animal);
        }

        else if((al_ptr.get())->TYPE == ObjectType::HERBIVORE)
        {
            list_save_object_ptr.herbivores.push_front(al_ptr);
            list_save_object_ptr.distance_to_herbivores.push_front(l_distane_to_animal);
        }
    }
}

/// Implemented
void Animal::find_plant(std::shared_ptr<Plant> pt_ptr)
{

    sf::Vector2f pl_coord = (pt_ptr.get())->get_position();
    double l_distane_to_plant = ut::compute_dist(this->coordinate, pl_coord);

    double l_iteraction_distance = 0.1;
    if (l_distane_to_plant < l_iteraction_distance){
        list_iteraction_objects_ptr.distance_to_plants.push_front(l_distane_to_plant);
        list_iteraction_objects_ptr.plants.push_front(pt_ptr);
    }

    double l_visible_distance = this->eyesight;
    if (l_distane_to_plant < l_visible_distance){
        list_visible_object_ptr.distance_to_plants.push_front(l_distane_to_plant);
        list_visible_object_ptr.plants.push_front(pt_ptr);
    }

    double l_save_object_distance = 10.0;
    if (l_distane_to_plant < l_save_object_distance){
        list_save_object_ptr.distance_to_plants.push_front(l_distane_to_plant);
        list_save_object_ptr.plants.push_front(pt_ptr);
    }

}

/// Implemented
sf::Vector2f Animal::get_position()
{
    return this->coordinate;
}

/// Implemented
sf::Vector2f Animal::get_velosity()
{
    return this->velosity;
}

// Not implemented
void Animal::reproduction(std::shared_ptr<Animal> ptr)
{
    this->last_reproduction = 0;
}

/// Implemented
bool Animal::is_reproductive_age()
{
    if (time_life > max_time_life / 10)
        return true;

    else
        return false;
}

/// Implemented
bool Animal::is_want_reproduction()
{
    if(is_reproductive_age()){
        if (last_reproduction > 10)
            return true;
    }

    return false;
}

/// Implemented
bool Animal::is_want_eat()
{
    if(bellyful.get() < 0.8)
        return true;
    else
        return false;
}

/// Implemented
void Animal::update_age()
{
    this->time_life++;
}

/// Implemented
void Animal::move_to_point(sf::Vector2f point)
{
    double x1 = coordinate.x, y1 = coordinate.y;
    double x2 = point.x, y2 = point.y;

    double dx = x2 - x1;
    double dy = y2 - y1;
    double d = sqrt(dx*dx + dy*dy);

    double l_cos = dx/d;
    double l_sin = dy/d;

    velosity.x = max_velosity * l_cos;
    velosity.y = max_velosity * l_sin;
}

/// Implemented
void Animal::move_from_point(sf::Vector2f point)
{
    double x1 = coordinate.x, y1 = coordinate.y;
    double x2 = point.x, y2 = point.y;

    double dx = x2 - x1;
    double dy = y2 - y1;
    double d = sqrt(dx*dx + dy*dy);

    double l_cos = dx/d;
    double l_sin = dy/d;

    velosity.x = - max_velosity * l_cos;
    velosity.y = - max_velosity * l_sin;
}

/// Implemented
void Animal::relax()
{

}

/// Implemented
double Animal::get_mass()
{
    return mass;
}

// Half implemented
void Animal::move(const float dt)
{
    if (coordinate.x < 0 && velosity.x < 0)
        velosity.x = -velosity.x;

    if (coordinate.x > 64 && velosity.x > 0)
        velosity.x = -velosity.x;

    if (coordinate.y < 0 && velosity.y < 0)
        velosity.y = -velosity.y;

    if (coordinate.y > 64 && velosity.y > 0)
        velosity.y = -velosity.y;

    coordinate.x = coordinate.x + velosity.x * dt;
    coordinate.y = coordinate.y + velosity.y * dt;
}
