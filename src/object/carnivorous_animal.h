#ifndef CARNIVOROUSANIMAL_H
#define CARNIVOROUSANIMAL_H

#include "animal.h"

#include <list>
#include "animal_genetic_code.h"

class CarnivorousAnimal : public Animal
{
private:
    void _eat(std::shared_ptr<Animal> ptr);

public:
    CarnivorousAnimal(AnimalGeneticCode genetic_code, sf::Vector2f coordinate);

    void update(const float dt);
    void draw(sf::RenderWindow &window, const float dt);
};

#endif // CARNIVOROUSANIMAL_H
