#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QIcon>
#include <QString>
#include <set>
#include "utils.h"
#include <iostream>

class Tile : public QObject, public std::enable_shared_from_this<Tile>  {
    Q_OBJECT
public:

    enum Type {
        zero, one, two, three, four, five, six, seven, eight, mine
    };

    explicit Tile(QObject* parent = nullptr, Type type = zero);

    [[nodiscard]] const QIcon& icon() const {
        static QIcon back(":/covered.png");
        static QIcon flagged(":/flag.png");
        return m_revealed ? m_front : (m_flagged ? flagged : back);
    }

    Type getType();

    void setType(Type type);

    bool isRevealed() const;

    bool isFlagged() const;

    std::map<RelativeAdjacencyIndex, std::shared_ptr<Tile>> getAdjacentTilesMap();

    std::shared_ptr<Tile> getAdjacentTile(RelativeAdjacencyIndex direction);

    void setAdjacentTile(RelativeAdjacencyIndex direction, const std::shared_ptr<Tile>& tile);

    void clearAdjacentTilesMap();

    signals:

    void stateChanged(std::shared_ptr<Tile> tile);

    void flagStateChanged(std::shared_ptr<Tile> tile);

public slots:

    void reveal();

    void revealAndEmitSignal();

    void flag();

    void flagAndEmitSignal();

    void updateNumAdjacentMines();

private:
    QIcon m_front;
    Type m_type;
    std::shared_ptr<Tile> m_north, m_east, m_south, m_west,
            m_northeast, m_northwest, m_southeast, m_southwest; // Adjacent tiles
    std::map<RelativeAdjacencyIndex, std::shared_ptr<Tile>> m_adjacentTilesMap;
    bool m_revealed = false;
    bool m_flagged = false;
};

#endif // TILE_H
