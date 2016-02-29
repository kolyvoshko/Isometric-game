/**
  * @file plant.h
  */

#ifndef PLANT_H
#define PLANT_H

#include <SFML/Graphics.hpp>

#include "interactive_object.h"

//#include "cartesian2d.h"
#include "genetic_code.h"
#include "plant_genetic_code.h"

class Plant : public InteractiveObject
{
private:
    PlantGeneticCode _genetic_code;

    sf::Vector2f _coordinate;

    bool _is_life;
    int _time_life;
    int _max_time_life;

    double _mass;
    double _max_mass;

    double _grown_rate;
    double _max_grown_rate;

    double _radius;
    double _max_radius;

public:
    Plant(PlantGeneticCode genetic_code, sf::Vector2f coordinate);

    sf::Vector2f get_position();
    double get_mass();

    bool is_live();
    void update_age();

    void find_neighborhood_object(std::list<InteractiveObject*> * obfects);
    void update(const float dt);
    void draw(sf::RenderWindow &window, const float dt);
};

#endif // PLANT_H
