#include <cassert>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QMessageBox>
#include <QThread>
#include <queue>

// Globals for tiles, columns, and rows. Necessary for window/grid resizing on startup.
int numTiles;
int numColumns;
int numRows;

std::default_random_engine MainWindow::m_generator; // NOLINT(cert-msc51-cpp)

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(nullptr), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QObject::connect(ui->startButton, SIGNAL(clicked()),
                     this, SLOT(callDepthFirstSearch()));

    // Message box prompt that displays before the primary grid window. This prompts users to choose their desired
    // maze size before creating the maze grid structure.
    QMessageBox msgBox;
    msgBox.setWindowTitle("Size Selection");
    msgBox.setText("Please pick your preferred maze size from the options below.");
    msgBox.setIcon(QMessageBox::Information);

    // Buttons for user. The close button is said to never be accessed but its inclusion is necessary and the button
    // itself functions.
    QPushButton *small = msgBox.addButton("Small", QMessageBox::AcceptRole);
    QPushButton *medium = msgBox.addButton("Medium", QMessageBox::AcceptRole);
    QPushButton *large = msgBox.addButton("Large", QMessageBox::AcceptRole);
    QPushButton *close = msgBox.addButton("Close", QMessageBox::RejectRole);
    msgBox.exec();

    // Perform different actions based on user choice. If the button clicked is small, medium, or large, set the
    // window size and grid size to a fixed amount, begin setting up the grid, exit the message prompt, and open the
    // main grid window. If the button clicked is close or the "X" button, close the program entirely.
    if (msgBox.clickedButton() == small) {
        this->setFixedSize(325,405);
        numColumns = numRows = 16;
        numTiles = numColumns * numRows;
        setupTiles(parent);
        return;
    }
    else if (msgBox.clickedButton() == medium) {
        this->setFixedSize(530,679);
        numColumns = numRows = 32;
        numTiles = numColumns * numRows;
        setupTiles(parent);
        return;
    }
    else if (msgBox.clickedButton() == large) {
        this->setFixedSize(786,935);
        numColumns = numRows = 48;
        numTiles = numColumns * numRows;
        setupTiles(parent);
        return;
    }
    else {
        exit(0);
    }
}

// Function that sets up the grid.
void MainWindow::setupTiles(QWidget* parent) {
    const QSize TILE_SIZE(16, 16);
    for (int i = 0; i < numTiles; ++i) {
        Tile::Type tileType;
        if (i == 0)
            tileType = Tile::start;
        else if (i == numTiles - 1)
            tileType = Tile::end;
        else
            tileType = Tile::empty;

        std::shared_ptr<Tile> tile = std::make_shared<Tile>(parent, tileType);
        if (tileType == Tile::start)
            m_start = tile;
        if (tileType == Tile::end)
            m_end = tile;
        m_tiles.push_back(tile);
        std::shared_ptr<TileButton> button = std::make_shared<TileButton>(parent, tile);

        button->setIcon(tile->icon());
        button->setIconSize(TILE_SIZE);
        button->setFixedSize(TILE_SIZE);
        button->setFlat(true);

        QObject::connect(button.get(), SIGNAL(clicked()),
                         tile.get(), SLOT(flipAndEmitSignal()));

        m_buttons.push_back(button);
        m_buttonMap.insert({tile, button});

        ui->gridLayout->addWidget(m_buttons.back().get(), i / numRows, i % numColumns);

        QObject::connect(tile.get(), SIGNAL(stateChanged(std::shared_ptr<Tile>)),
                         this, SLOT(tileClicked(std::shared_ptr<Tile>)));

    }
    setAdjacentTiles();
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
                            tile.get(), SLOT(flipAndEmitSignal()));
    }
    m_buttonMap.clear();
    for (int i = 0; i < numTiles; ++i) { // Reconnect all buttons
        m_buttons[i]->setTile(m_tiles[i]);
        m_buttonMap.insert({m_tiles[i], m_buttons[i]});
        std::shared_ptr<Tile> tile = m_buttons[i]->getTile();
        QObject::connect(m_buttons[i].get(), SIGNAL(clicked()),
                         m_tiles[i].get(), SLOT(flipAndEmitSignal()));
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
}


void MainWindow::setAdjacentTiles() {
    for (const auto& tile : m_tiles) {
        tile->clearAdjacentTilesMap();
    }

    // Create class instance for direction.
    RelativeAdjacencyIndex adjIdx(numColumns);

    for (int i = 0; i < numTiles; ++i) {

        // Bools for making sure tiles on an edge do not have an adjacent tile set to a tile
        // which may be adjacent to it index-wise but is actually not adjacent to it on the grid
        bool notLeftEdge = (i % numColumns != 0);
        bool notRightEdge = (i % numColumns != numColumns - 1);

        std::shared_ptr<Tile> currTile = m_tiles[i];

        if (i + adjIdx.getNorth() >= 0) {
            assert(m_tiles[i + adjIdx.getNorth()]);
            currTile->setAdjacentTile(adjIdx.getNorth(), m_tiles[i + adjIdx.getNorth()]);
        }
        if (notRightEdge && i + adjIdx.getEast() < numTiles) {
            assert(m_tiles[i + adjIdx.getEast()]);
            currTile->setAdjacentTile(adjIdx.getEast(), m_tiles[i + adjIdx.getEast()]);
        }
        if (i + adjIdx.getSouth() < numTiles) {
            assert(m_tiles[i + adjIdx.getSouth()]);
            currTile->setAdjacentTile(adjIdx.getSouth(), m_tiles[i + adjIdx.getSouth()]);
        }
        if (notLeftEdge && i + adjIdx.getWest() >= 0) {
            assert(m_tiles[i + adjIdx.getWest()]);
            currTile->setAdjacentTile(adjIdx.getWest(), m_tiles[i + adjIdx.getWest()]);
        }
    }
}

void MainWindow::clearWalls() {
}

void MainWindow::breadthFirstSearch() {
//    std::vector<std::shared_ptr<Tile>> visited;
//    std::queue<std::shared_ptr<Tile>> q;
//    q.push(m_start->getAdjacentTile(south));
//    std::cout<< m_start->getAdjacentTilesMap().size();
//    while (!q.empty()){
//        std::shared_ptr<Tile> tile = q.back();
//        std::cout<< tile;
//        q.pop();
//        auto adjacentTilesMap = tile->getAdjacentTilesMap();
//        for (const auto& pair : adjacentTilesMap) {
//            std::shared_ptr<Tile> adjacentTile = pair.second;
//            bool tileVisited = false;
//            for (const auto& visitedTile : visited){
//                if (adjacentTile == visitedTile){
//                    tileVisited = true;
//                    break;
//                }
//            }
//            if (!tileVisited){
//                visited.push_back(adjacentTile);
//                q.push(adjacentTile);
//                adjacentTile->setType(Tile::traverse);
//                QThread::sleep(1);
//                sync();
//                QWidget::repaint();
//            }
//        }
//    }
}

// Calls depthFirstSearch. This is the only way for it to function properly at the moment.
void MainWindow::callDepthFirstSearch() {
    depthFirstSearch(m_start);
}

// Depth first search algorithm.
bool MainWindow::depthFirstSearch(const std::shared_ptr<Tile>& tile) {
    auto adjacentTilesMap = tile->getAdjacentTilesMap();
    for (const auto& pair : adjacentTilesMap) {
        std::shared_ptr<Tile> adjacentTile = pair.second;
        if (adjacentTile && adjacentTile->getType() == Tile::empty){
            adjacentTile->setType(Tile::traverse);
            QThread::msleep(100);
            sync();
            QWidget::repaint();
            if(depthFirstSearch(adjacentTile))
                return true;
        }
        else if (adjacentTile && adjacentTile->getType() == Tile::end){
            sync();
            return true;
        }
    }
    return false;
}


void MainWindow::revealConnectedTiles(const std::shared_ptr<Tile>& tile) { // NOLINT(misc-no-recursion)
//    Tile::Type tileType = tile->getType();
//    auto adjacentTilesMap = tile->getAdjacentTilesMap();
//    for (const auto& pair : adjacentTilesMap) {
//        std::shared_ptr<Tile> adjacentTile = pair.second;
//        Tile::Type adjTileType = adjacentTile->getType();
//        if (!adjacentTile->isWall() && tileType == Tile::empty) {
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
    auto messageBox = new QMessageBox(QMessageBox::Information, "Maze Algorithms", message);
    messageBox->setAttribute(Qt::WA_DeleteOnClose, true);
    QObject::connect(messageBox, SIGNAL(buttonClicked(QAbstractButton*)),
                     this, SLOT(reset(QAbstractButton*)));
    messageBox->exec();
}