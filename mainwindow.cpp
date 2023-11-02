#include <cassert>
#include <algorithm>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <iostream>
#include <QMessageBox>

std::default_random_engine MainWindow::m_generator; // NOLINT(cert-msc51-cpp)

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(nullptr), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_remainingFlags = NUMBER_OF_MINES;
    const QSize TILE_SIZE(16, 16);
    for (int i = 0; i < NUMBER_OF_TILES; ++i) {
        Tile::Type tileType = Tile::empty;
        std::shared_ptr<Tile> tile = std::make_shared<Tile>(parent, tileType);
        m_tiles.push_back(tile);
        std::shared_ptr<TileButton> button = std::make_shared<TileButton>(parent, tile);

        button->setIcon(tile->icon());
        button->setIconSize(TILE_SIZE);
        button->setFixedSize(TILE_SIZE);
        button->setFlat(true);

        QObject::connect(button.get(), SIGNAL(clicked()),
                         tile.get(), SLOT(revealAndEmitSignal()));

        m_buttons.push_back(button);
        m_buttonMap.insert({tile, button});

        ui->gridLayout->addWidget(m_buttons.back().get(), i / NUMBER_OF_COLUMNS, i % NUMBER_OF_ROWS);

        QObject::connect(tile.get(), SIGNAL(stateChanged(std::shared_ptr<Tile>)),
                         this, SLOT(tileClicked(std::shared_ptr<Tile>)));
        QObject::connect(tile.get(), SIGNAL(flagStateChanged(std::shared_ptr<Tile>)),
                         this, SLOT(tileRightClicked(std::shared_ptr<Tile>)));

    }

    shuffle();
    sync();

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::quit() {
    QApplication::quit();
}

void MainWindow::sync() {
    for (const auto& tile : m_tiles) { // Disconnect all buttons
        QObject::disconnect(m_buttonMap.at(tile).get(), SIGNAL(clicked()),
                            tile.get(), SLOT(revealAndEmitSignal()));
    }
    m_buttonMap.clear();
    for (int i = 0; i < NUMBER_OF_TILES; ++i) { // Reconnect all buttons
        m_buttons[i]->setTile(m_tiles[i]);
        m_buttonMap.insert({m_tiles[i], m_buttons[i]});
        std::shared_ptr<Tile> tile = m_buttons[i]->getTile();
        QObject::connect(m_buttons[i].get(), SIGNAL(clicked()),
                         m_tiles[i].get(), SLOT(revealAndEmitSignal()));
    }
    auto tileIt = m_tiles.begin();
    auto buttonIt = m_buttons.begin();
    while (tileIt != m_tiles.end()) { // Update all icons
        (*buttonIt)->setIcon((*tileIt)->icon());
        ++tileIt;
        ++buttonIt;
    }
    assert(buttonIt == m_buttons.end());
}

void MainWindow::tileClicked(const std::shared_ptr<Tile>& tile) {
    tile->flip();
    setAdjacentTiles();
    sync();
}

void MainWindow::tileRightClicked(const std::shared_ptr<Tile>& tile) {
    if (tile->isFlagged()) {
        m_remainingFlags -= 1;
    }
    else {
        m_remainingFlags += 1;
    }
    sync();
}


void MainWindow::setAdjacentTiles() {
    for (const auto& tile : m_tiles) {
        tile->clearAdjacentTilesMap();
    }
    for (int i = 0; i < NUMBER_OF_TILES; ++i) {

        // Bools for making sure tiles on an edge do not have an adjacent tile set to a tile
        // which may be adjacent to it index-wise but is actually not adjacent to it on the grid
        bool notLeftEdge = (i % 16 != 0);
        bool notRightEdge = (i % 16 != NUMBER_OF_COLUMNS - 1);

        std::shared_ptr<Tile> currTile = m_tiles[i];

        if (i + north >= 0) {
            assert(m_tiles[i + north]);
            currTile->setAdjacentTile(north, m_tiles[i + north]);
        }
        if (notRightEdge && i + east < NUMBER_OF_TILES) {
            assert(m_tiles[i + east]);
            currTile->setAdjacentTile(east, m_tiles[i + east]);
        }
        if (i + south < NUMBER_OF_TILES) {
            assert(m_tiles[i + south]);
            currTile->setAdjacentTile(south, m_tiles[i + south]);
        }
        if (notLeftEdge && i + west >= 0) {
            assert(m_tiles[i + west]);
            currTile->setAdjacentTile(west, m_tiles[i + west]);
        }
        if (notRightEdge && i + northeast >= 0) {
            assert(m_tiles[i + northeast]);
            currTile->setAdjacentTile(northeast, m_tiles[i + northeast]);
        }
        if (notLeftEdge && i + northwest >= 0) {
            assert(m_tiles[i + northwest]);
            currTile->setAdjacentTile(northwest, m_tiles[i + northwest]);
        }
        if (notRightEdge && i + southeast < NUMBER_OF_TILES) {
            assert(m_tiles[i + southeast]);
            currTile->setAdjacentTile(southeast, m_tiles[i + southeast]);
        }
        if (notLeftEdge && i + southwest < NUMBER_OF_TILES) {
            assert(m_tiles[i + southwest]);
            currTile->setAdjacentTile(southwest, m_tiles[i + southwest]);
        }
    }
}

void MainWindow::reset(QAbstractButton* button) {
    for (const auto& tile : m_tiles) {
        if (tile->isWall()) {
            tile->flip();
        }
        if (tile->isFlagged()) {
            tile->flag();
        }
    }
    m_numClearedTiles = 0;
    m_remainingFlags = NUMBER_OF_FLAGS;
    shuffle();
}

void MainWindow::shuffle() {
    std::shuffle(m_tiles.begin(), m_tiles.end(), m_generator);
    if (m_firstTileRevealed) {
        setAdjacentTiles();
        emit boardGenerated();
    }
    sync();
}

// Recursively reveal all connected "empty" tiles until a bomb-adjacent tile is revealed
void MainWindow::revealConnectedTiles(const std::shared_ptr<Tile>& tile) { // NOLINT(misc-no-recursion)
//    Tile::Type tileType = tile->getType();
//    auto adjacentTilesMap = tile->getAdjacentTilesMap();
//    for (const auto& pair : adjacentTilesMap) {
//        std::shared_ptr<Tile> adjacentTile = pair.second;
//        Tile::Type adjTileType = adjacentTile->getType();
//        if (!adjacentTile->isWall() && tileType == Tile::empty && !adjacentTile->isFlagged()) {
//            if (adjTileType == Tile::empty) {
//                adjacentTile->flip();
//                m_numClearedTiles += 1;
//                revealConnectedTiles(adjacentTile);
//            }
//            else if (adjTileType != Tile::mine) {
//                adjacentTile->flip();
//                m_numClearedTiles += 1;
//            }
//        }
//    }
}

void MainWindow::message(const QString& message) const {
    auto messageBox = new QMessageBox(QMessageBox::Information, "Mine Sweeper", message);
    messageBox->setAttribute(Qt::WA_DeleteOnClose, true);
    if (message != NO_FLAGS_MESSAGE) {
        QObject::connect(messageBox, SIGNAL(buttonClicked(QAbstractButton*)),
                         this, SLOT(reset(QAbstractButton*)));
    }
    messageBox->exec();
}