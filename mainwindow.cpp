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

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(nullptr), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QObject::connect(ui->startButton, SIGNAL(clicked()),
                     this, SLOT(callAlgorithm()));
    QObject::connect(ui->clearButton, SIGNAL(clicked()),
                     this, SLOT(clearWalls()));
    QObject::connect(ui->resetButton, SIGNAL(clicked()),
                     this, SLOT(resetAlgorithm()));
    QObject::connect(ui->generateButton, SIGNAL(clicked()),
                     this, SLOT(initializeMazeGen()));

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
        this->setFixedSize(250,370);
        numColumns = numRows = 15;
        numTiles = numColumns * numRows;
        setupTiles(parent);
        return;
    }
    else if (msgBox.clickedButton() == medium) {
        this->setFixedSize(450,600);
        numColumns = numRows = 31;
        numTiles = numColumns * numRows;
        setupTiles(parent);
        return;
    }
    else if (msgBox.clickedButton() == large) {
        this->setFixedSize(700,850);
        numColumns = numRows = 47;
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
        std::shared_ptr<TileButton> button = std::make_shared<TileButton>(parent, tile, i / numRows, i % numColumns);

        button->setIcon(tile->icon());
        button->setIconSize(TILE_SIZE);
        button->setFixedSize(TILE_SIZE);
        button->setFlat(true);
        button->setMouseTracking(true);

        QObject::connect(button.get(), SIGNAL(clicked()),
                         tile.get(), SLOT(flipAndEmitSignal()));
        QObject::connect(button.get(), SIGNAL(drag(int, int)),
                         this, SLOT(tileDraggedOver(int, int)));

        m_buttons.push_back(button);
        m_buttonMap.insert({tile, button});

        ui->gridLayout->addWidget(m_buttons.back().get(), i / numRows, i % numColumns);

        QObject::connect(tile.get(), SIGNAL(stateChanged(std::shared_ptr<Tile>)),
                         this, SLOT(tileClicked(std::shared_ptr<Tile>)));

    }

    initializeGraph();
    setAdjacentTiles();
    syncAll();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::quit() {
    QApplication::quit();
}

void MainWindow::tileDraggedOver(int row, int col) {
    // Assuming you have a way to access the TileButton at the specified row and col
    TileButton* tileButton = getTileButtonAt(row, col);

    if (tileButton) {
        // Get the tile from the TileButton and flip it
        std::shared_ptr<Tile> tile = tileButton->getTile();
        if (tile->getType() == Tile::empty) {
            tileClicked(tile);
        }
    }
}

TileButton* MainWindow::getTileButtonAt(int row, int col) {
    for (const auto& button : m_buttons) {
        if (button->getRow() == row && button->getColumn() == col) {
            return button.get();
        }
    }
    return nullptr;
}

void MainWindow::syncAll() {
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

void MainWindow::syncTile(const std::shared_ptr<Tile> &tile) {
    m_buttonMap[tile]->setIcon(tile->icon());
}

void MainWindow::tileClicked(const std::shared_ptr<Tile>& tile) {
    tile->flip();
    setAdjacentTiles();
    syncAll();
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
void MainWindow::setAdjacentVertices() {

    for (const auto& tile : m_tiles) {
        tile->clearAdjacentTilesMap();
    }

    // Create class instance for direction.
    RelativeVertexAdjacencyIndex adjVertexIdx(numColumns);
    RelativeAdjacencyIndex adjEdgeIdx(numColumns);

    for (int i = 0; i < numTiles; ++i) {
        // Bools for making sure tiles on an edge do not have an adjacent tile set to a tile
        // which may be adjacent to it index-wise but is actually not adjacent to it on the grid
        bool notLeftEdge = (i % numColumns != 0);
        bool notRightEdge = (i % numColumns != numColumns - 1);

        std::shared_ptr<Tile> currTile = m_tiles[i];

        if (currTile->getNodeType() == Tile::vertex){
            if (i + adjVertexIdx.getNorth() >= 0) {
                assert(m_tiles[i + adjVertexIdx.getNorth()]);
                currTile->setAdjacentEdgeVertex(adjVertexIdx.getNorth(), {m_tiles[i + adjEdgeIdx.getNorth()], m_tiles[i + adjVertexIdx.getNorth()]});
            }
            if (notRightEdge && i + adjVertexIdx.getEast() < numTiles) {
                assert(m_tiles[i + adjVertexIdx.getEast()]);
                currTile->setAdjacentEdgeVertex(adjVertexIdx.getEast(), {m_tiles[i + adjEdgeIdx.getEast()], m_tiles[i + adjVertexIdx.getEast()]});
            }
            if (i + adjVertexIdx.getSouth() < numTiles) {
                assert(m_tiles[i + adjVertexIdx.getSouth()]);
                currTile->setAdjacentEdgeVertex(adjVertexIdx.getSouth(), {m_tiles[i + adjEdgeIdx.getSouth()], m_tiles[i + adjVertexIdx.getSouth()]});
            }
            if (notLeftEdge && i + adjVertexIdx.getWest() >= 0) {
                assert(m_tiles[i + adjVertexIdx.getWest()]);
                currTile->setAdjacentEdgeVertex(adjVertexIdx.getWest(), {m_tiles[i + adjEdgeIdx.getWest()], m_tiles[i + adjVertexIdx.getWest()]});
            }
        }
    }
}

// Clear all maze walls that have been placed/generated.
void MainWindow::clearWalls() {

    for (int i = 0; i < numTiles; ++i) {

        // Reset maze connection state to allow for more maze generation after wall clearing.
        m_tiles[i]->setConnectedToMaze(false);

        if (m_tiles[i]->getType() == Tile::wall){
            m_tiles[i]->setType(Tile::empty);
        }
    }

    // Unblock generate button to allow presses.
    ui->generateButton->blockSignals(false);

    syncAll();
}

void MainWindow::resetAlgorithm() {

    for (int i = 0; i < numTiles; ++i) {
        if (m_tiles[i]->getType() == Tile::traverse){
            m_tiles[i]->setType(Tile::empty);
        }
    }

    setAdjacentTiles();
    syncAll();
}

// Calls a search algorithm depending on user choice.
void MainWindow::callAlgorithm() {

    // Block all signals before entering to prevent buttons from being pressed during search. After search is completed,
    // allow button presses to happen.
    ui->centralwidget->blockSignals(true);

    // Extract the chosen algorithm from the dropdown menu and call its function.
    QString algorithmChoice = ui->algorithmBox->currentText();
    if (algorithmChoice.toStdString() == "Depth-First") {
        depthFirstSearch(m_start);
    }
    else if (algorithmChoice.toStdString() == "Random") {
        randomSearch(m_start);
    }

    ui->centralwidget->blockSignals(false);
}

// Depth first search algorithm.
bool MainWindow::depthFirstSearch(const std::shared_ptr<Tile>& tile) {

    auto adjacentTilesMap = tile->getAdjacentTilesMap();
    for (const auto& pair : adjacentTilesMap) {
        std::shared_ptr<Tile> adjacentTile = pair.second;
        if (adjacentTile && adjacentTile->getType() == Tile::empty){
            adjacentTile->setType(Tile::traverse);

            // Change traversal speed depending on maze size. Slower speed is only applied to small mazes to allow
            // user to understand traversal.
            if (numColumns == 15) {
                QThread::msleep(50);
            }
            else {
                QThread::msleep(10);
            }

            syncTile(adjacentTile);
            m_buttonMap[adjacentTile]->repaint();
            if(depthFirstSearch(adjacentTile)) {
                return true;
            }
        }
        else if (adjacentTile && adjacentTile->getType() == Tile::end){
            syncTile(adjacentTile);
            return true;
        }
    }
    return false;
}

// Random Search Function
bool MainWindow::randomSearch(const std::shared_ptr<Tile> &tile) {

    auto adjacentTilesMap = tile->getAdjacentTilesMap();
    std::vector<std::pair<int, std::shared_ptr<Tile>>> pairs;

    for (const auto& pair : adjacentTilesMap) {
        pairs.emplace_back(pair);
    }

    while (!pairs.empty()) {

        // Pick a random vertex/edge in the map to connect with.
        int idx = std::rand() % pairs.size();
        auto pair = pairs.at(idx);
        std::shared_ptr<Tile> adjacentTile = pair.second;
        pairs.erase(pairs.begin() + idx);

        if (adjacentTile && adjacentTile->getType() == Tile::empty){
            adjacentTile->setType(Tile::traverse);

            // Change traversal speed depending on maze size. Slower speed is only applied to small mazes to allow
            // user to understand traversal.
            if (numColumns == 15) {
                QThread::msleep(50);
            }
            else {
                QThread::msleep(10);
            }

            syncTile(adjacentTile);
            m_buttonMap[adjacentTile]->repaint();
            if(randomSearch(adjacentTile)) {
                return true;
            }
        }
        else if (adjacentTile && adjacentTile->getType() == Tile::end){
            syncTile(adjacentTile);
            return true;
        }
    }
    return false;
}

void MainWindow::initializeGraph() {

    int row;
    int column;

    for (int i = 0; i < numTiles; ++i) {
        row = std::ceil(i/numRows) + 1;
        column = (i % numColumns) + 1;

        // Vertices
        if (row % 2 == 1 && column % 2 == 1) {
            m_tiles[i]->setNodeType(Tile::vertex);
            m_vertices.push_back(m_tiles[i]);
        }

        // Edges
        else if ((row + column) % 2 == 1) {
            m_tiles[i]->setNodeType(Tile::edge);
        }
    }

    setAdjacentVertices();
}

void MainWindow::initializeMazeGen() {

    // Reset algorithm just in case user forgets to do so before making a new maze.
    resetAlgorithm();

    // Clear walls just in case user drew on board before deciding to generate.
    clearWalls();

    int row;
    int column;

    // Visualize.
    for (int i = 0; i < numTiles; ++i) {
        row = std::ceil(i / numRows) + 1;
        column = (i % numColumns) + 1;

        // Visualize Walls
        if (row % 2 == 0 && column % 2 == 0) {
            m_tiles[i]->setType(Tile::wall);
        }
            // Visualize Edges
        else if ((row + column) % 2 == 1) {
            m_tiles[i]->setType(Tile::wall);
        }
    }

    generateMaze(m_start);

    // Block button from being pressed. This signal will be unblocked when walls are cleared.
    ui->generateButton->blockSignals(true);

    syncAll();
}

bool MainWindow::generateMaze(const std::shared_ptr<Tile>& tile) {

    auto adjacentVerticesMap = tile->getAdjacentEdgeVerticesMap();

    std::vector<std::pair<std::shared_ptr<Tile>, std::shared_ptr<Tile>>> pairs;

    for (const auto& pair : adjacentVerticesMap) {
        pairs.push_back(pair.second);
    }

    while (!pairs.empty()) {

        // Pick a random vertex/edge in the map to connect with.
        int idx = std::rand() % pairs.size();
        auto pair = pairs.at(idx);
        std::shared_ptr<Tile> adjacentEdge = pair.first;
        std::shared_ptr<Tile> adjacentVertex = pair.second;
        pairs.erase(pairs.begin() + idx);

        if (!adjacentVertex->isConnectedToMaze()) {
            adjacentEdge->setType(Tile::empty);
            adjacentVertex->setConnectedToMaze(true);

            if (generateMaze(adjacentVertex)) {
                return true;
            }
        }
    }
    return false;
}
