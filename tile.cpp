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
        case path:
            m_empty = QIcon(":/path.png");
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
        case path:
            m_empty = QIcon(":/path.png");
            break;
    }
}

bool Tile::isWall() const {
    return m_is_wall;
}

std::map<RelativeAdjacencyIndex, std::shared_ptr<Tile>> Tile::getAdjacentTilesMap() {
    return m_adjacentTilesMap;
}

std::shared_ptr<Tile> Tile::getAdjacentTile(RelativeAdjacencyIndex direction) {
    return m_adjacentTilesMap[direction];
}

void Tile::setAdjacentTile(RelativeAdjacencyIndex direction, const std::shared_ptr<Tile>& tile) {
    m_adjacentTilesMap.insert({direction, tile});
}

void Tile::clearAdjacentTilesMap() {
    m_adjacentTilesMap.clear();
}

void Tile::flip() {
    if (m_type == Type::empty) m_type = Type::wall;
    else if (m_type == Type::wall) m_type = Type::empty;
}

void Tile::flipAndEmitSignal() {
    m_is_wall = !m_is_wall;
    emit stateChanged(shared_from_this());
}