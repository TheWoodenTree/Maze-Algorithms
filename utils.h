//
// Created by Aaron Hall on 3/14/23.
//

#ifndef MINE_SWEEPER_UTILS_H
#define MINE_SWEEPER_UTILS_H

static const int NUMBER_OF_ROWS = 48;
static const int NUMBER_OF_COLUMNS = 48;
static const int NUMBER_OF_TILES = NUMBER_OF_ROWS * NUMBER_OF_COLUMNS;
static const int NUMBER_OF_MINES = 360;
static const int NUMBER_OF_FLAGS = NUMBER_OF_MINES;
static const int NUMBER_OF_CLEARABLE_TILES = NUMBER_OF_TILES - NUMBER_OF_MINES;

static const QString WIN_MESSAGE = "You've won!";
static const QString LOSE_MESSAGE = "You've lost.";
static const QString NO_FLAGS_MESSAGE = "You have no flags left!";

enum RelativeAdjacencyIndex {
    north = -NUMBER_OF_COLUMNS, east = 1, south = NUMBER_OF_COLUMNS, west = -1,
    northeast = north + east, northwest = north + west,
    southeast = south + east, southwest = south + west
};

#endif //MINE_SWEEPER_UTILS_H
