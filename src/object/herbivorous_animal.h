#ifndef HERBIVOROUSANIMAL_H
#define HERBIVOROUSANIMAL_H

#include <SFML/System.hpp>

#include "animal.h"
#include "animal_genetic_code.h"


class HerbivorousAnimal : public Animal
{
private:
    void _eat(std::shared_ptr<Plant> ptr);

public:
    HerbivorousAnimal(sf::Vector2f coordinate);
    HerbivorousAnimal(AnimalGeneticCode genetic_code, sf::Vector2f coordinate);

    void update(const float dt);
    void draw(sf::RenderWindow &window, const float dt);
};


#endif // HERBIVOROUSANIMAL_H
