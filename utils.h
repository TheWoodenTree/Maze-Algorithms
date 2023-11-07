//
// Created by Aaron Hall on 3/14/23.
//

#ifndef MAZE_ALGORITHMS_UTILS_H
#define MAZE_ALGORITHMS_UTILS_H

static const int NUMBER_OF_ROWS = 32;
static const int NUMBER_OF_COLUMNS = 32;
static const int NUMBER_OF_TILES = NUMBER_OF_ROWS * NUMBER_OF_COLUMNS;

enum RelativeAdjacencyIndex {
    north = -NUMBER_OF_COLUMNS, east = 1, south = NUMBER_OF_COLUMNS, west = -1,
    northeast = north + east, northwest = north + west,
    southeast = south + east, southwest = south + west
};

#endif //MAZE_ALGORITHMS_H
