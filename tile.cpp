#include "tile.h"
#include <cassert>
#include <iostream>

Tile::Tile(QObject* parent, Type type) : QObject(parent), m_type(type) {
    switch (type) {
        case wall:
            m_empty = QIcon(":/wall.png");
            break;
        case empty:
            m_empty = QIcon(":/empty.png");
            break;
        case start:
            m_empty = QIcon(":/start.png");
            break;
        case end:
            m_empty = QIcon(":/end.png");
            break;
        case traverse:
            m_empty = QIcon(":/traverse.png");
            break;
    }
    assert(!m_empty.isNull());
}

Tile::Type Tile::getType() {
    return m_type;
}

void Tile::setType(Type type)  {
    m_type = type;
    switch (type) {
        case wall:
            m_empty = QIcon(":/wall.png");
            break;
        case empty:
            m_empty = QIcon(":/empty.png");
            break;
        case start:
            m_empty = QIcon(":/start.png");
            break;
        case end:
            m_empty = QIcon(":/end.png");
            break;
        case traverse:
            m_empty = QIcon(":/traverse.png");
            break;
    }
}

Tile::NodeType Tile::getNodeType() {
    return n_type;
}

void Tile::setNodeType(NodeType nodeType) {
    n_type = nodeType;
}

bool Tile::isWall() const {
    return m_is_wall;
}

std::map<int, std::shared_ptr<Tile>> Tile::getAdjacentTilesMap() {
    return m_adjacentTilesMap;
}

std::shared_ptr<Tile> Tile::getAdjacentTile(int direction) {
    return m_adjacentTilesMap[direction];
}

void Tile::setAdjacentTile(int direction, const std::shared_ptr<Tile>& tile) {
    m_adjacentTilesMap.insert({direction, tile});
}

void Tile::clearAdjacentTilesMap() {
    m_adjacentTilesMap.clear();
}

std::map<int, std::pair<std::shared_ptr<Tile>, std::shared_ptr<Tile>>> Tile::getAdjacentEdgeVerticesMap() {
    return m_adjacentEdgeVertexMap;
}
std::pair<std::shared_ptr<Tile>, std::shared_ptr<Tile>> Tile::getAdjacentEdgeVertex(int direction) {
    return m_adjacentEdgeVertexMap[direction];
}
void Tile::setAdjacentEdgeVertex(int direction, const std::pair<std::shared_ptr<Tile>, std::shared_ptr<Tile>> &edgeVertexPair) {
    m_adjacentEdgeVertexMap.insert({direction, edgeVertexPair});
}
void Tile::clearAdjacentEdgeVerticesMap() {
    m_adjacentEdgeVertexMap.clear();
}

bool Tile::isConnectedToMaze() const {
    return m_isinMaze;
}

void Tile::setConnectedToMaze(bool condition) {
    m_isinMaze = condition;
}

void Tile::flip() {
    if (m_type == Type::empty) m_type = Type::wall;
    else if (m_type == Type::wall) m_type = Type::empty;
}

void Tile::flipAndEmitSignal() {
    m_is_wall = !m_is_wall;
    emit stateChanged(shared_from_this());
}