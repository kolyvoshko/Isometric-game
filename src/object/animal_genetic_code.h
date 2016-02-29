/**
  * @file animal_genetic_code.h
  */

#ifndef ANIMALGENETICCODE_H
#define ANIMALGENETICCODE_H

#include "genetic_code.h"

class AnimalGeneticCode: public GeneticCode
{
public:
    AnimalGeneticCode();

    int max_time_life;

    double max_length;
    double max_width;

    double max_velosity;
    double max_acceleration;
    double max_turn;
    double max_eyesight;
    double max_mass;

    double carnivorous; // can have value 0..1
    double herbivorous; // can have value 0..1

    void mutation();
    GeneticCode chossing(GeneticCode genetic_code);

    AnimalGeneticCode create_carnivorous_code();
    AnimalGeneticCode create_herbivorous_code();
};

#endif // ANIMALGENETICCODE_H
