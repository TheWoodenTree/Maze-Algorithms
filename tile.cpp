#include "tile.h"
#include <cassert>
#include <iostream>

Tile::Tile(QObject* parent, Type type) : QObject(parent), m_type(type) {
    switch (type) {
        case zero:
            m_front = QIcon(":/0.png");
            break;
        case one:
            m_front = QIcon(":/1.png");
            break;
        case two:
            m_front = QIcon(":/2.png");
            break;
        case three:
            m_front = QIcon(":/3.png");
            break;
        case four:
            m_front = QIcon(":/4.png");
            break;
        case five:
            m_front = QIcon(":/5.png");
            break;
        case six:
            m_front = QIcon(":/6.png");
            break;
        case seven:
            m_front = QIcon(":/7.png");
            break;
        case eight:
            m_front = QIcon(":/8.png");
            break;
        case mine:
            m_front = QIcon(":/mine.png");
            break;
    }
    assert(!m_front.isNull());
}

Tile::Type Tile::getType() {
    return m_type;
}

void Tile::setType(Type type)  {
    m_type = type;
    switch (type) {
        case zero:
            m_front = QIcon(":/0.png");
            break;
        case one:
            m_front = QIcon(":/1.png");
            break;
        case two:
            m_front = QIcon(":/2.png");
            break;
        case three:
            m_front = QIcon(":/3.png");
            break;
        case four:
            m_front = QIcon(":/4.png");
            break;
        case five:
            m_front = QIcon(":/5.png");
            break;
        case six:
            m_front = QIcon(":/6.png");
            break;
        case seven:
            m_front = QIcon(":/7.png");
            break;
        case eight:
            m_front = QIcon(":/8.png");
            break;
        case mine:
            m_front = QIcon(":/mine.png");
            break;
    }
}

bool Tile::isRevealed() const {
    return m_revealed;
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

void Tile::updateNumAdjacentMines() {
    int numAdjacentMines = 0;
    for (const auto& adjacentTile : m_adjacentTilesMap) {
        if (adjacentTile.second->getType() == mine) {
            ++numAdjacentMines;
        }
    }
    setType(Type(numAdjacentMines));
}

void Tile::reveal() {
    m_revealed = !m_revealed;
}

void Tile::revealAndEmitSignal() {
    m_revealed = !m_revealed;
    emit stateChanged(shared_from_this());
}

void Tile::flag() {
    m_flagged = !m_flagged;
}

void Tile::flagAndEmitSignal() {
    m_flagged = !m_flagged;
    emit flagStateChanged(shared_from_this());
}