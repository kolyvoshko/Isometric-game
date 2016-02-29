#ifndef UTILS2D_H
#define UTILS2D_H

#include <list>

#include "window_value.h"

namespace ut
{
    class WindowValue;
    float compute_dist(sf::Vector2f &pos, sf::Vector2f &pos2);
    int get_index_min_element(std::list<float> l);
}

#endif // UTILS2D_H
