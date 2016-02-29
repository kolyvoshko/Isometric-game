/**
  * @file animal_genetic_code.cpp
  */

#include "animal_genetic_code.h"

AnimalGeneticCode::AnimalGeneticCode():
    GeneticCode()
{

}


AnimalGeneticCode AnimalGeneticCode::create_carnivorous_code(){
    AnimalGeneticCode carnivorous_code;

    carnivorous_code.carnivorous = 1.0;
    carnivorous_code.herbivorous = 0.0;

    carnivorous_code.max_turn = 0.2;
    carnivorous_code.max_velosity = 0.1;
    carnivorous_code.max_acceleration = 0.0;

    carnivorous_code.max_eyesight = 5.0;
    carnivorous_code.max_mass = 1.0;

    carnivorous_code.max_length = 0.1;
    carnivorous_code.max_width = 0.05;

    carnivorous_code.max_time_life = 2;

    return carnivorous_code;
}


AnimalGeneticCode AnimalGeneticCode::create_herbivorous_code(){
    AnimalGeneticCode herbivorous_code;

    herbivorous_code.carnivorous = 0.0;
    herbivorous_code.herbivorous = 1.0;

    herbivorous_code.max_turn = 0.2;
    herbivorous_code.max_velosity = 0.1;
    herbivorous_code.max_acceleration = 0.0;

    herbivorous_code.max_eyesight = 5.0;
    herbivorous_code.max_mass = 1.0;

    herbivorous_code.max_length = 0.1;
    herbivorous_code.max_width = 0.05;

    herbivorous_code.max_time_life = 100;

    return herbivorous_code;
}
