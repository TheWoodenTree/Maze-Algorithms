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
        case one:
            m_empty = QIcon(":/1.png");
            break;
        case two:
            m_empty = QIcon(":/2.png");
            break;
        case three:
            m_empty = QIcon(":/3.png");
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
        case one:
            m_empty = QIcon(":/1.png");
            break;
        case two:
            m_empty = QIcon(":/2.png");
            break;
        case three:
            m_empty = QIcon(":/3.png");
            break;
    }
}

bool Tile::isWall() const {
    return m_is_wall;
}

bool Tile::isFlagged() const {
    return m_flagged;
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

void Tile::revealAndEmitSignal() {
    m_is_wall = !m_is_wall;
    emit stateChanged(shared_from_this());
}

void Tile::flag() {
    m_flagged = !m_flagged;
}

void Tile::flagAndEmitSignal() {
    m_flagged = !m_flagged;
    emit flagStateChanged(shared_from_this());
}