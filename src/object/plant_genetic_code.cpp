/**
  * @file plant_genetic_code.cpp
  */

#include "plant_genetic_code.h"

PlantGeneticCode::PlantGeneticCode():
    GeneticCode()
{
    this->max_grown_rate = 1.0;
    this->max_mass = 1.0;
    this->max_radius = 1.0;
    this->max_time_life = 10.0;
}


