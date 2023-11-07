#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QIcon>
#include <QString>
#include <set>
#include "utils.h"
#include <iostream>

class Tile : public QObject, public std::enable_shared_from_this<Tile> {
Q_OBJECT
public:

    enum Type {
        wall, empty, start, end, path
    };

    explicit Tile(QObject *parent = nullptr, Type type = empty);

    [[nodiscard]] const QIcon &icon() const {
        static QIcon wall(":/wall.png");
        static QIcon empty(":/empty.png");
        static QIcon start(":/start.png");
        static QIcon end(":/end.png");
        switch (m_type) {
            case Type::empty:
                return empty;
                break;
            case Type::wall:
                return wall;
                break;
            case Type::start:
                return start;
                break;
            case Type::end:
                return end;
                break;
            default:
                return empty;
        }
    }

    Type getType();

    void setType(Type type);

    bool isWall() const;

    std::map<RelativeAdjacencyIndex, std::shared_ptr<Tile>> getAdjacentTilesMap();

    std::shared_ptr<Tile> getAdjacentTile(RelativeAdjacencyIndex direction);

    void setAdjacentTile(RelativeAdjacencyIndex direction, const std::shared_ptr<Tile> &tile);

    void clearAdjacentTilesMap();

signals:

    void stateChanged(std::shared_ptr<Tile> tile);

public slots:

    void flip();

    void flipAndEmitSignal();

private:
    QIcon m_empty;
    Type m_type;
    std::shared_ptr<Tile> m_north, m_east, m_south, m_west,
            m_northeast, m_northwest, m_southeast, m_southwest; // Adjacent tiles
    std::map<RelativeAdjacencyIndex, std::shared_ptr<Tile>> m_adjacentTilesMap;
    bool m_is_wall = false;
};
#endif // TILE_H
