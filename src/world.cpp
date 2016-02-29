#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

#include "world.h"
#include "tile.h"

#include "object/plant.h"
#include "object/plant_genetic_code.h"

#include "object/animal.h"
#include "object/herbivorous_animal.h"
#include "object/carnivorous_animal.h"
#include "object/animal_genetic_code.h"

void World::bulldoze(const Tile& tile)
{
    /* Replace the selected tiles on the map with the tile and
     * update populations etc accordingly */
    for(int pos = 0; pos < this->map.width * this->map.height; ++pos)
    {
        if(this->map.selected[pos] == 1)
        {
            if(this->map.tiles[pos].tileType == TileType::RESIDENTIAL)
            {
                this->population_plant += this->map.tiles[pos].population;
            }
            else if(this->map.tiles[pos].tileType == TileType::COMMERCIAL)
            {
                this->population_herbivorus += this->map.tiles[pos].population;
            }
            else if(this->map.tiles[pos].tileType == TileType::INDUSTRIAL)
            {
                this->population_carnivorus += this->map.tiles[pos].population;
            }
            this->map.tiles[pos] = tile;
        }
    }

    return;
}
void World::shuffleTiles()
{
    while(this->shuffledTiles.size() < this->map.tiles.size())
    {
        this->shuffledTiles.push_back(0);
    }
    std::iota(shuffledTiles.begin(), shuffledTiles.end(), 1);
    std::random_shuffle(shuffledTiles.begin(), shuffledTiles.end());

    return;
}
void World::tileChanged()
{
    this->map.updateDirection(TileType::ROAD);
    this->map.findConnectedRegions(
    {
        TileType::ROAD, TileType::RESIDENTIAL,
        TileType::COMMERCIAL, TileType::INDUSTRIAL
    }, 0);

    return;
}
void World::generate_plants(int number)
{
    PlantGeneticCode plain_genetic_code;

    plain_genetic_code.max_grown_rate = 1.0;
    plain_genetic_code.max_mass = 1.0;
    plain_genetic_code.max_radius = 1.0;
    plain_genetic_code.max_time_life = 1000;

    for(int i=0; i<number;++i)
    {
        sf::Vector2f point;
        point.x = static_cast<float> (rand()) * this->map.width / RAND_MAX;
        point.y = static_cast<float> (rand()) * this->map.height / RAND_MAX;

        Plant * plant = new Plant(plain_genetic_code, point);

        this->map.add_interactive_obfect(plant);
    }
}
void World::generate_carnivorous(int number)
{
    AnimalGeneticCode animal_genetic_code;

    for (int i=0; i < number; ++i){
        sf::Vector2f point;
        point.x = static_cast<float> (rand()) * this->map.width / RAND_MAX;
        point.y = static_cast<float> (rand()) * this->map.height / RAND_MAX;

        AnimalGeneticCode carnivorous_code = animal_genetic_code.create_carnivorous_code();

        Animal * animal = new CarnivorousAnimal(carnivorous_code, point);

        this->map.add_interactive_obfect(animal);
    }
}
void World::generate_herbivorous(int number)
{
    AnimalGeneticCode animal_genetic_code;

    for (int i=0; i < number; ++i){
        sf::Vector2f point;
        point.x = static_cast<float> (rand()) * this->map.width / RAND_MAX;
        point.y = static_cast<float> (rand()) * this->map.height / RAND_MAX;

        AnimalGeneticCode herbivorus_code = animal_genetic_code.create_herbivorous_code();

        Animal * animal = new HerbivorousAnimal(herbivorus_code, point);

        this->map.add_interactive_obfect(animal);
    }
}
void World::load(std::string worldName, std::map<std::string, Tile>& tileAtlas)
{
	int width = 0;
	int height = 0;
	
    std::ifstream inputFile(worldName + "_cfg.dat", std::ios::in);
	
	std::string line;
	
	while(std::getline(inputFile, line))
	{
	    std::istringstream lineStream(line);
	    std::string key;
	    if(std::getline(lineStream, key, '='))
	    {
	            std::string value;
	            if(std::getline(lineStream, value))
	            {
                    if     (key == "width")             width                   = std::stoi(value);
		            else if(key == "height")            height                  = std::stoi(value);
		            else if(key == "day")               this->day               = std::stoi(value);
		            else if(key == "funds")             this->funds             = std::stod(value);
//		            else if(key == "earnings")          this->earnings          = std::stod(value);
	            }
	            else
	            {
		            std::cerr << "Error, no value for key " << key << std::endl;
	            }
	    }
	}
	
	inputFile.close();
	
    this->map.load(worldName + "_map.dat", width, height, tileAtlas);
    tileChanged();

    srand( time(NULL) );
    this->generate_plants(20);
    this->generate_herbivorous(20);
    this->generate_carnivorous(20);
	
	return;
}
void World::save(std::string worldName)
{
    std::ofstream outputFile(worldName + "_cfg.dat", std::ios::out);
    
    outputFile << "width="              << this->map.width          << std::endl;
    outputFile << "height="             << this->map.height         << std::endl;
    outputFile << "day="                << this->day                << std::endl;
    outputFile << "populationPool="     << this->population_plant     << std::endl;
    outputFile << "employmentPool="     << this->population_herbivorus     << std::endl;
    outputFile << "funds="              << this->funds              << std::endl;
//    outputFile << "earnings="           << this->earnings           << std::endl;
    
    outputFile.close();
    
    this->map.save(worldName + "_map.dat");
    
    return;
}
void World::update(float dt)
{
    /* Update the game time */
    this->currentTime += dt;
    if(this->currentTime < this->timePerDay) return;
    ++day;
    this->currentTime = 0.0;

    this->map.update(dt);

    return;
}
