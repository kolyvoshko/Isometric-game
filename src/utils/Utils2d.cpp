#include <list>

#include "Utils2d.h"


float ut::compute_dist(sf::Vector2f &pos, sf::Vector2f &pos2)
{
    return sqrt(
                (pos.x - pos2.x)*(pos.x - pos2.x) +
                (pos.y - pos2.y)*(pos.y - pos2.y)
                );
}


int ut::get_index_min_element(std::list<float> l)
{
    double min= 0.0;
    int id = 0;
    int id_min = 0;

    for(std::list<float>::iterator
        it =  l.begin(),
        end = l.end();
        it != end; ++it
        )
    {
        if (*it <= min){
            id_min = id;
            min = *it;
        }

        id++;
    }

    return id_min;
}
