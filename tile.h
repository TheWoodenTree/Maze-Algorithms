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
        wall, empty, one, two, three, four, five, six, seven, eight, mine
    };

    explicit Tile(QObject* parent = nullptr, Type type = empty);

    [[nodiscard]] const QIcon& icon() const {
        std::cout << m_is_wall << std::endl;
        static QIcon wall(":/wall.png");
        static QIcon empty(":/empty.png");
        //switch (m_type) {
        //    case Type::empty: return empty; break;
        //    case Type::wall: return wall; break;
        //}
        return m_is_wall ? wall : empty;
    }

    Type getType();

    void setType(Type type);

    bool isWall() const;

    bool isFlagged() const;

    std::map<RelativeAdjacencyIndex, std::shared_ptr<Tile>> getAdjacentTilesMap();

    std::shared_ptr<Tile> getAdjacentTile(RelativeAdjacencyIndex direction);

    void setAdjacentTile(RelativeAdjacencyIndex direction, const std::shared_ptr<Tile>& tile);

    void clearAdjacentTilesMap();

    signals:

    void stateChanged(std::shared_ptr<Tile> tile);

    void flagStateChanged(std::shared_ptr<Tile> tile);

public slots:

    void flip();

    void revealAndEmitSignal();

    void flag();

    void flagAndEmitSignal();

private:
    QIcon m_empty;
    Type m_type;
    std::shared_ptr<Tile> m_north, m_east, m_south, m_west,
            m_northeast, m_northwest, m_southeast, m_southwest; // Adjacent tiles
    std::map<RelativeAdjacencyIndex, std::shared_ptr<Tile>> m_adjacentTilesMap;
    bool m_is_wall = false;
    bool m_flagged = false;
};

#endif // TILE_H
