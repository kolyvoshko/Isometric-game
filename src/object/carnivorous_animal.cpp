#include <list>

#include "carnivorous_animal.h"

#include "../utils/Utils2d.h"


CarnivorousAnimal::CarnivorousAnimal(AnimalGeneticCode genetic_code, sf::Vector2f coordinate)
    : Animal(genetic_code, coordinate)
{
    this->TYPE = ObjectType::CARNIVORE;
    this->draw_object.setRadius(10.0f);
    this->draw_object.setScale(1.0, 0.5f);
    this->draw_object.setFillColor(sf::Color::Red);
}


void CarnivorousAnimal::update(const float dt)
{
    // update parameters
    this->last_reproduction++;
    this->bellyful *= 0.9999;

    this->move(dt);

    // dead
    if (time_life > max_time_life){
        is_life = false;
        return;
    }

    // dead
    if (bellyful.get() == 0){
        is_life = false;
        return;
    }

    // iteraction distance
    // reproduction
    if (list_iteraction_objects_ptr.predators.size() != 0){
        std::list<std::shared_ptr<Animal> >::iterator it =
                list_iteraction_objects_ptr.predators.begin();

        if (is_reproductive_age() && (* it->get()).is_reproductive_age() ){

            this->reproduction(*it);
            list_iteraction_objects_ptr.predators.remove(*it);

            return;
        }
    }

    // eat
    if (list_iteraction_objects_ptr.herbivores.size() != 0){
        std::list<std::shared_ptr<Animal> >::iterator it =
                list_iteraction_objects_ptr.herbivores.begin();

        this->_eat(*it);
        list_iteraction_objects_ptr.herbivores.remove(*it);

        return;
    }

    // visible distation
    bool l_has_task = false;

    // If want reproduction begins to parthner
    if (list_visible_object_ptr.predators.size() != 0){
        l_has_task = true;

        double id_min_distance =
                ut::get_index_min_element(list_visible_object_ptr.distance_to_predators);

        std::list<std::shared_ptr<Animal> >::iterator iter =
                list_visible_object_ptr.predators.begin();

        std::advance(iter, id_min_distance);

        move_to_point((*iter->get()).get_position());
        return;
    }

    // If want eat begins to herbivore
    if (list_visible_object_ptr.herbivores.size() != 0){
        l_has_task = true;

        double id_min_distance =
                ut::get_index_min_element(list_visible_object_ptr.distance_to_herbivores);

        std::list<std::shared_ptr<Animal> >::iterator iter =
                list_visible_object_ptr.herbivores.begin();

        std::advance(iter, id_min_distance);

        move_to_point((*iter->get()).get_position());
        return;
    }

    // else
    if (!l_has_task){
        this->relax();
    }
}

/// Implemented
void CarnivorousAnimal::_eat(std::shared_ptr<Animal> ptr)
{
    double food = ptr->get_mass() / mass;
    bellyful += food;
}


void CarnivorousAnimal::draw(sf::RenderWindow &window, const float dt)
{
    window.draw(this->draw_object);
}
