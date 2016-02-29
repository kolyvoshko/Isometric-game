/**
  * @file plant.cpp
  */

#include "plant.h"


Plant::Plant(PlantGeneticCode genetic_code, sf::Vector2f coordinate):
    _genetic_code(genetic_code),
    _coordinate(coordinate)
{
    this->TYPE = ObjectType::PLANT;
    this->_is_life = true;

    this->_max_grown_rate   = this->_genetic_code.max_grown_rate;
    this->_max_mass         = this->_genetic_code.max_mass;
    this->_max_radius       = this->_genetic_code.max_radius;
    this->_max_time_life    = this->_genetic_code.max_time_life;

    this->draw_object.setRadius(10.0f);
    this->draw_object.setScale(1.0, 0.5f);
    this->draw_object.setFillColor(sf::Color::Green);
}


void Plant::update(const float dt)
{
    if (_time_life > _max_time_life)
        this->_is_life = false;
}


sf::Vector2f Plant::get_position()
{
    return this->_coordinate;
}


void Plant::update_age()
{
    this->_time_life++;
}

void Plant::find_neighborhood_object(std::list<InteractiveObject *> *obfects)
{

}


bool Plant::is_live()
{
    return this->_is_life;
}


void Plant::draw(sf::RenderWindow &window, const float dt)
{
    window.draw(this->draw_object);
}

double Plant::get_mass()
{
    return _mass;
}
