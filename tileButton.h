//
// Created by Aaron Hall on 3/14/23.
//

#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include <QPushButton>
#include "tile.h"
#include <QSinglePointEvent>

class TileButton : public QPushButton, public std::enable_shared_from_this<TileButton> {
    Q_OBJECT

public:
    explicit TileButton(QWidget* parent, std::shared_ptr<Tile>& tile);

    std::shared_ptr<Tile> getTile();

    void setTile(const std::shared_ptr<Tile>& tile);

    signals:

    void rightClicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    std::shared_ptr<Tile> m_tile;
};


#endif //TILEBUTTON_H
