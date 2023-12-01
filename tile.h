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
        wall, empty, start, end, traverse
    };

    enum NodeType {
        vertex, edge
    };

    explicit Tile(QObject *parent = nullptr, Type type = empty);

    [[nodiscard]] const QIcon &icon() const {
        static QIcon wall(":/wall.png");
        static QIcon empty(":/empty.png");
        static QIcon start(":/start.png");
        static QIcon end(":/end.png");
        static QIcon traverse(":/traverse.png");
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
            case Type::traverse:
                return traverse;
                break;
            default:
                return empty;
        }
    }

    Type getType();

    void setType(Type type);

    NodeType getNodeType();
    void setNodeType(NodeType nodeType);

    bool isWall() const;

    std::map<int, std::shared_ptr<Tile>> getAdjacentTilesMap();

    std::shared_ptr<Tile> getAdjacentTile(int direction);

    void setAdjacentTile(int direction, const std::shared_ptr<Tile> &tile);

    void clearAdjacentTilesMap();

    void setAdjacentEdgeVertex(int direction, const std::pair<std::shared_ptr<Tile>, std::shared_ptr<Tile>> &edgeVertexPair);
    std::map<int, std::pair<std::shared_ptr<Tile>, std::shared_ptr<Tile>>> getAdjacentEdgeVerticesMap();
    std::pair<std::shared_ptr<Tile>, std::shared_ptr<Tile>> getAdjacentEdgeVertex(int direction);
    void clearAdjacentEdgeVerticesMap();

    bool isConnectedToMaze() const;
    void setConnectedToMaze(bool condition);

signals:

    void stateChanged(std::shared_ptr<Tile> tile);

public slots:

    void flip();

    void flipAndEmitSignal();

private:
    QIcon m_empty;
    Type m_type;
    NodeType n_type;
    std::shared_ptr<Tile> m_north, m_east, m_south, m_west,
            m_northeast, m_northwest, m_southeast, m_southwest; // Adjacent tiles
    std::map<int, std::shared_ptr<Tile>> m_adjacentTilesMap;

    std::map<int, std::pair<std::shared_ptr<Tile>, std::shared_ptr<Tile>>> m_adjacentEdgeVertexMap;
    bool m_isinMaze = false;

    bool m_is_wall = false;
};
#endif // TILE_H