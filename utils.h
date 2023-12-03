//
// Created by Aaron Hall on 3/14/23.
//

#ifndef MAZE_ALGORITHMS_UTILS_H
#define MAZE_ALGORITHMS_UTILS_H

class RelativeAdjacencyIndex {
public:
    explicit RelativeAdjacencyIndex(int numColumns) {
        north = -numColumns;
        east = 1;
        south = numColumns;
        west = -1;
    }

    int getNorth() const {
        return north;
    }

    int getEast() const {
        return east;
    }

    int getSouth() const {
        return south;
    }

    int getWest() const {
        return west;
    }

private:
    int north;
    int east;
    int south;
    int west;
};

class RelativeVertexAdjacencyIndex {
public:
    explicit RelativeVertexAdjacencyIndex(int numColumns) {
        north = -numColumns*2;
        east = 2;
        south = numColumns*2;
        west = -2;
    }

    int getNorth() const {
        return north;
    }

    int getEast() const {
        return east;
    }

    int getSouth() const {
        return south;
    }

    int getWest() const {
        return west;
    }

private:
    int north;
    int east;
    int south;
    int west;
};

#endif //MAZE_ALGORITHMS_UTILS_H
