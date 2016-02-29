/**
  * @file plant_genetic_code.h
  */

#ifndef PLANTGENETICCODE_H
#define PLANTGENETICCODE_H

#include "genetic_code.h"

class PlantGeneticCode: public GeneticCode
{
public:
    PlantGeneticCode();

    int max_time_life;

    double max_grown_rate;
    double max_mass;
    double max_radius;

    void mutation();
    GeneticCode chossing(GeneticCode genetic_code);
};

#endif // PLANTGENETICCODE_H
