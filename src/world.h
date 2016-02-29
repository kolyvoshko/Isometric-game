#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <map>

#include "map.h"

class World
{
private:

    float currentTime;
    float timePerDay;

    std::vector<int> shuffledTiles;

public:

    int population_plant;
    int population_herbivorus;
    int population_carnivorus;

    Map map;

    /* Running total of city earnings (from tax etc) this month */
//    double earnings;
    double funds;

    int day;

    World()
    {
        this->currentTime = 0.0;
        this->timePerDay = 1.0;
        this->day = 0;

        /// integrate
        this->population_plant = 0;
        this->population_herbivorus = 0;
        this->population_carnivorus = 0;
    }

    World(std::string worldName, int tileSize, std::map<std::string, Tile>& tileAtlas) : World()
    {
        this->map.tileSize = tileSize;
        load(worldName, tileAtlas);
    }

    void load(std::string worldName, std::map<std::string, Tile>& tileAtlas);
    void save(std::string worldName);

    void update(float dt);
    void bulldoze(const Tile& tile);
    void shuffleTiles();
    void tileChanged();

    // Generate world
    void generate_plants(int number);
    void generate_carnivorous(int number);
    void generate_herbivorous(int number);
};

#endif /* WORLD_HPP */
