#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include <memory>
#include <random>
#include "tile.h"
#include "tileButton.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow() override;



signals:

    void boardGenerated();

private slots:

    static void quit();

    void syncAll();

    void tileClicked(const std::shared_ptr<Tile>& tile);

    void tileRightClicked(const std::shared_ptr<Tile>& tile);

    void setAdjacentTiles();

    void tileDraggedOver(int row, int col);

    TileButton* getTileButtonAt(int row, int col);

    void clearWalls();

    void resetAlgorithm();

    void setAdjacentVertices();

    void initializeGraph();

    void initializeMazeGen();

    bool generateMaze(const std::shared_ptr<Tile>& tile);

    void syncTile(const std::shared_ptr<Tile>& tile);

    bool randomSearch(const std::shared_ptr<Tile>& tile);

    void breadthFirstSearch();

    void callAlgorithm();

    bool depthFirstSearch(const std::shared_ptr<Tile>& tile);

    void revealConnectedTiles(const std::shared_ptr<Tile>& tile);

    void message(const QString& message) const;

    void setupTiles(QWidget* parent);

private:
    Ui::MainWindow* ui;
    std::vector<std::shared_ptr<TileButton>> m_buttons;
    std::vector<std::shared_ptr<Tile>> m_tiles;

    std::vector<std::shared_ptr<Tile>> m_vertices;
    std::vector<std::shared_ptr<Tile>> randomTiles;

    std::shared_ptr<Tile> m_start;
    std::shared_ptr<Tile> m_end;
    std::map<std::shared_ptr<Tile>, std::shared_ptr<TileButton>> m_buttonMap;
    static std::default_random_engine m_generator;
};

#endif // MAINWINDOW_H