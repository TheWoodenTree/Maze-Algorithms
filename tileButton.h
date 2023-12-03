//
// Created by Aaron Hall on 3/14/23.
//

#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include <QPushButton>
#include <QApplication>
#include "tile.h"
#include <QSinglePointEvent>
#include <QVBoxLayout>

class TileButton : public QPushButton, public std::enable_shared_from_this<TileButton> {
    Q_OBJECT

public:
    explicit TileButton(QWidget* parent, std::shared_ptr<Tile>& tile, int row, int col);

    std::shared_ptr<Tile> getTile();

    void setTile(const std::shared_ptr<Tile>& tile);

    int getRow() const;

    int getColumn() const;

    signals:

    void drag(int row, int col);

    void rightClicked();


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    std::shared_ptr<Tile> m_tile;
    bool isDragging = false;
    int m_row;
    int m_col;
};


#endif //TILEBUTTON_H
