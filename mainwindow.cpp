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
    ui->flagsLabel->setText("Flags: " + QString::number(m_remainingFlags) + "/" + QString::number(NUMBER_OF_FLAGS));
    ui->clearedLabel->setText("Cleared: 0/" + QString::number(NUMBER_OF_CLEARABLE_TILES));
    const QSize TILE_SIZE(16, 16);
    for (int i = 0; i < NUMBER_OF_TILES; ++i) {
        Tile::Type tileType = Tile::zero;
        if (i < NUMBER_OF_MINES) {
            tileType = Tile::mine;
        }
        std::shared_ptr<Tile> tile = std::make_shared<Tile>(parent, tileType);
        m_tiles.push_back(tile);
        std::shared_ptr<TileButton> button = std::make_shared<TileButton>(parent, tile);

        button->setIcon(tile->icon());
        button->setIconSize(TILE_SIZE);
        button->setFixedSize(TILE_SIZE);
        button->setFlat(true);

        QObject::connect(button.get(), SIGNAL(clicked()),
                         tile.get(), SLOT(revealAndEmitSignal()));
        QObject::connect(button.get(), SIGNAL(rightClicked()),
                         this, SLOT(checkIfFlagsLeft()));

        m_buttons.push_back(button);
        m_buttonMap.insert({tile, button});

        ui->gridLayout->addWidget(m_buttons.back().get(), i / NUMBER_OF_COLUMNS, i % NUMBER_OF_ROWS);

        if (tile->getType() != Tile::mine) {
            QObject::connect(this, SIGNAL(boardGenerated()),
                             (tile.get()), SLOT(updateNumAdjacentMines()));
        }

        QObject::connect(tile.get(), SIGNAL(stateChanged(std::shared_ptr<Tile>)),
                         this, SLOT(tileClicked(std::shared_ptr<Tile>)));
        QObject::connect(tile.get(), SIGNAL(flagStateChanged(std::shared_ptr<Tile>)),
                         this, SLOT(tileRightClicked(std::shared_ptr<Tile>)));

    }

    shuffle();
    sync();

    QObject::connect(ui->shuffleButton, SIGNAL(clicked()),
                     this, SLOT(shuffle()));
    QObject::connect(ui->quitButton, SIGNAL(clicked()),
                     this, SLOT(quit()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateFlagsLabel(int remainingFlags) {
    ui->flagsLabel->setText("Flags: " + QString::number(remainingFlags) + "/" + QString::number(NUMBER_OF_FLAGS));
}

void MainWindow::updateClearedTilesLabel(int numClearedTiles) {
    ui->clearedLabel->setText(
            "Cleared: " + QString::number(numClearedTiles) + "/" + QString::number(NUMBER_OF_CLEARABLE_TILES));
}

void MainWindow::quit() {
    QApplication::quit();
}

void MainWindow::sync() {
    for (const auto& tile : m_tiles) {
        QObject::disconnect(m_buttonMap.at(tile).get(), SIGNAL(clicked()),
                            tile.get(), SLOT(revealAndEmitSignal()));
        QObject::disconnect(m_buttonMap.at(tile).get(), SIGNAL(rightClicked()),
                            this, SLOT(checkIfFlagsLeft()));
    }
    m_buttonMap.clear();
    for (int i = 0; i < NUMBER_OF_TILES; ++i) {
        m_buttons[i]->setTile(m_tiles[i]);
        m_buttonMap.insert({m_tiles[i], m_buttons[i]});
        std::shared_ptr<Tile> tile = m_buttons[i]->getTile();
        if (!tile->isRevealed() && !tile->isFlagged()) { // Disallow revealing revealed or flagged tiles
            QObject::connect(m_buttons[i].get(), SIGNAL(clicked()),
                             m_tiles[i].get(), SLOT(revealAndEmitSignal()));
        }
        if (!tile->isRevealed()) { // Disallow flagging revealed tiles
            QObject::connect(m_buttons[i].get(), SIGNAL(rightClicked()),
                             this, SLOT(checkIfFlagsLeft()));
        }
    }
    auto tileIt = m_tiles.begin();
    auto buttonIt = m_buttons.begin();
    while (tileIt != m_tiles.end()) {
        (*buttonIt)->setIcon((*tileIt)->icon());
        ++tileIt;
        ++buttonIt;
    }
    assert(buttonIt == m_buttons.end());
}

void MainWindow::tileClicked(const std::shared_ptr<Tile>& tile) {
    if (!m_firstTileRevealed) {
        m_firstTileRevealed = true;
        if (tile->getType() == Tile::mine) {
            for (const auto& currTile : m_tiles) {
                if (currTile->getType() == Tile::zero && currTile != tile) {
                    currTile->setType(Tile::mine);
                    QObject::connect(this, SIGNAL(boardGenerated()),
                                        tile.get(), SLOT(updateNumAdjacentMines()));
                    QObject::disconnect(this, SIGNAL(boardGenerated()),
                                     currTile.get(), SLOT(updateNumAdjacentMines()));
                    break;
                }
            }
            tile->setType(Tile::zero);
        }
        setAdjacentTiles();
        emit boardGenerated();
    }
    if (tile->getType() != Tile::mine) {
        m_numClearedTiles += 1;
        updateClearedTilesLabel(m_numClearedTiles);
        revealConnectedTiles(tile);
    }
    else {
        tile->reveal();
        for (const auto& currTile : m_tiles) {
            if (currTile->getType() == Tile::mine) {
                currTile->reveal();
            }
        }
        sync();
        message(LOSE_MESSAGE);
        return;
    }

    sync();
    if (m_numClearedTiles == NUMBER_OF_CLEARABLE_TILES) { message(WIN_MESSAGE); }
}

void MainWindow::tileRightClicked(const std::shared_ptr<Tile>& tile) {
    if (tile->isFlagged()) {
        m_remainingFlags -= 1;
    }
    else {
        m_remainingFlags += 1;
    }
    updateFlagsLabel(m_remainingFlags);
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
        if (tile->isRevealed()) {
            tile->reveal(); // Reset to being covered up. Bad name, I know, but I'm too lazy to change it now.
        }
        if (tile->isFlagged()) {
            tile->flag();
        }
    }
    m_numClearedTiles = 0;
    m_remainingFlags = NUMBER_OF_FLAGS;
    updateClearedTilesLabel(m_numClearedTiles);
    updateFlagsLabel(m_remainingFlags);
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

// Recursively reveal all connected "zero" tiles until a bomb-adjacent tile is revealed
void MainWindow::revealConnectedTiles(const std::shared_ptr<Tile>& tile) { // NOLINT(misc-no-recursion)
    Tile::Type tileType = tile->getType();
    auto adjacentTilesMap = tile->getAdjacentTilesMap();
    for (const auto& pair : adjacentTilesMap) {
        std::shared_ptr<Tile> adjacentTile = pair.second;
        Tile::Type adjTileType = adjacentTile->getType();
        if (!adjacentTile->isRevealed() && tileType == Tile::zero && !adjacentTile->isFlagged()) {
            if (adjTileType == Tile::zero) {
                adjacentTile->reveal();
                m_numClearedTiles += 1;
                updateClearedTilesLabel(m_numClearedTiles);
                revealConnectedTiles(adjacentTile);
            }
            else if (adjTileType != Tile::mine) {
                adjacentTile->reveal();
                m_numClearedTiles += 1;
                updateClearedTilesLabel(m_numClearedTiles);
            }
        }
    }
}

void MainWindow::checkIfFlagsLeft() {
    auto button = qobject_cast<TileButton*>(sender());
    if (m_remainingFlags > 0 || button->getTile()->isFlagged()) {
        button->getTile()->flagAndEmitSignal();
    }
    else {
        message(NO_FLAGS_MESSAGE);
    }
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