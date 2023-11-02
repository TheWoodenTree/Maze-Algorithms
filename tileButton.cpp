//
// Created by Aaron Hall on 3/14/23.
//

#include "tileButton.h"

TileButton::TileButton(QWidget* parent, std::shared_ptr<Tile>& tile) : m_tile(tile) {}

void TileButton::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::MouseButton::LeftButton) {
        emit clicked();
    }
    else if (event->button() == Qt::MouseButton::RightButton) {
        emit rightClicked();
    }
}

std::shared_ptr<Tile> TileButton::getTile() {
    return m_tile;
}

void TileButton::setTile(const std::shared_ptr<Tile>& tile) {
    m_tile = tile;
}
