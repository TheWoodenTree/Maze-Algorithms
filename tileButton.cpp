//
// Created by Aaron Hall on 3/14/23.
//

#include "tileButton.h"
#include <QGridLayout>

TileButton::TileButton(QWidget* parent, std::shared_ptr<Tile>& tile, int row, int col)
        : QPushButton(parent), m_row(row), m_col(col) {
}

void TileButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MouseButton::LeftButton) {
        isDragging = true;
    }
}

void TileButton::mouseMoveEvent(QMouseEvent *event) {
    if (isDragging && event->buttons() & Qt::LeftButton) {
        // Calculate the position of the cursor relative to the top-left corner of the widget
        QPoint relativePos = event->pos();

        // Map the relative position to the parent (which should be the layout)
        QPoint positionInLayout = mapToParent(relativePos);

        // Calculate the row and column of the tile under the cursor
        int row = positionInLayout.y() / height() - 5;  // Assuming each TileButton has the same height
        int col = positionInLayout.x() / width() - 1;   // Assuming each TileButton has the same width

        qDebug() << "Event position:" << positionInLayout << "Row:" << row << "Column:" << col;

        // Emit a signal to notify that the tile under the cursor is being dragged over
        emit drag(row, col);
    }
}

void TileButton::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (isDragging) {
            // Emit clicked() only if the mouse has not moved significantly
            emit clicked();
        }
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked();
    }

    isDragging = false;
}

int TileButton::getRow() const {
    return m_row;
}

int TileButton::getColumn() const {
    return m_col;
}

std::shared_ptr<Tile> TileButton::getTile() {
    return m_tile;
}

void TileButton::setTile(const std::shared_ptr<Tile>& tile) {
    m_tile = tile;
}
