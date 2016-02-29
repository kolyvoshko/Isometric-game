/**
  * @file animal.h
  */

#ifndef ANIMAL_H
#define ANIMAL_H

#include <memory>
#include <list>

#include <SFML/Graphics.hpp>

#include "interactive_object.h"

#include "../utils/Utils2d.h"
#include "../map.h"

#include "genetic_code.h"
#include "animal_genetic_code.h"
#include "plant.h"

class Animal;


struct ListObjects
{
    std::list<float> distance_to_plants;
    std::list<float> distance_to_herbivores;
    std::list<float> distance_to_predators;

    std::list<std::shared_ptr<Plant> > plants;
    std::list<std::shared_ptr<Animal> > herbivores;
    std::list<std::shared_ptr<Animal> > predators;
};


class Animal : public InteractiveObject
{
public:
    Animal(AnimalGeneticCode genetic_code, sf::Vector2f coordinate);

    AnimalGeneticCode genetic_code;

    sf::Vector2f coordinate;
    sf::Vector2f velosity;
    sf::Vector2f acceleration;
    mutable double   max_velosity;
    mutable double   max_acceleration;

    // animal options
    double          length;        // NOT USE
    mutable double  max_length;    // NOT USE
    double          width;         // NOT USE
    mutable double  max_width;     // NOT USE
    double          turn;          // NOT USE
    mutable double  max_turn;
    int             time_life;     /// time life(old) animal
    mutable int     max_time_life; /// maximum time life of animal
    double          eyesight;      /// radius of eye
    mutable double  max_eyesight;  /// max radius of eye
    double          mass;          /// mass of animal
    mutable double  max_mass;      // NOT USE
    bool            is_life;

    // window values
    ut::WindowValue bellyful;    // can have value 0..1

    // lists object pointers
    ListObjects list_iteraction_objects_ptr;  /// @brief Lists of iteraction object pointers
    ListObjects list_visible_object_ptr;      /// @brief Lists of iteraction object pointers
    ListObjects list_save_object_ptr;         /// @brief Lists of save object pointers

    // functions

    void find_neighborhood_object(std::list<InteractiveObject*> * obfects);

    void find_animal(std::shared_ptr<Animal> al_ptr);
    void find_plant(std::shared_ptr<Plant> pt_ptr);

    bool is_live();
    void update_age();

    void live();
    double get_mass();

    void update(const float dt){}
    void draw(sf::RenderWindow &window, const float dt){}
    sf::Vector2f get_position();
    sf::Vector2f get_velosity();

    // eat
    bool is_want_eat();

    // reproduction
    int last_reproduction;
    bool is_reproductive_age();
    bool is_want_reproduction();
    void reproduction(std::shared_ptr<Animal> ptr);

    // move
    void move(const float dt);                                /// @brief update coordinate
    void move_to_point(sf::Vector2f point);     /// @brief update velosity
    void move_from_point(sf::Vector2f point);   /// @brief update velosity

    void relax();
};

#endif // ANIMAL_H
