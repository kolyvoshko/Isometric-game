#include "object_manager.h"

#include "plant.h"
#include "carnivorous_animal.h"
#include "herbivorous_animal.h"

#include "plant_genetic_code.h"
#include "animal_genetic_code.h"


std::string objectTypeToStr(ObjectType type)
{
    switch(type)
    {
        default:
        case ObjectType::VOID:				return "Void";
        case ObjectType::PLANT:				return "Plant";
        case ObjectType::ANIMAL:			return "Animal";
        case ObjectType::HERBIVORE:         return "Herbivore";
        case ObjectType::CARNIVORE:			return "Carbivore";
    }
}


void ObjectManager::updateNeigborhood()
{
    for (std::list<InteractiveObject *>::iterator it = this->objects.begin(), end = this->objects.end();
             it != end; ++it)
    {
        for (std::list<InteractiveObject *>::iterator jt = it; ++jt != this->objects.end(); ){

        }

    }
}

ObjectManager::ObjectManager()
{
}

void ObjectManager::createObject(std::string objType, sf::Vector2f pos)
{
    if (objType == objectTypeToStr(ObjectType::PLANT)){
        PlantGeneticCode code;
        InteractiveObject * obj = new Plant(code, pos);
        this->objects.push_front(obj);
    }

    if (objType == objectTypeToStr(ObjectType::HERBIVORE)){
        AnimalGeneticCode animal_code;
        AnimalGeneticCode h_code = animal_code.create_herbivorous_code();
        InteractiveObject * obj = new HerbivorousAnimal(h_code, pos);
        this->objects.push_front(obj);
    }

    if (objType == objectTypeToStr(ObjectType::CARNIVORE)){
        AnimalGeneticCode animal_code;
        AnimalGeneticCode h_code = animal_code.create_carnivorous_code();
        InteractiveObject * obj = new CarnivorousAnimal(h_code, pos);
        this->objects.push_front(obj);
    }
}

void ObjectManager::updateObjects()
{
    static int updateStep = 10;
    if (updateStep <= 0){
        updateStep = 10;
        this->updateNeigborhood();
    }
    else{
        updateStep--;
    }

}





