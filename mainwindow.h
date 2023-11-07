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

    void sync();

    void tileClicked(const std::shared_ptr<Tile>& tile);

    void tileRightClicked(const std::shared_ptr<Tile>& tile);

    void setAdjacentTiles();

    void clearWalls();

    void revealConnectedTiles(const std::shared_ptr<Tile>& tile);

    void message(const QString& message) const;

private:
    Ui::MainWindow* ui;
    std::vector<std::shared_ptr<TileButton>> m_buttons;
    std::vector<std::shared_ptr<Tile>> m_tiles;
    std::map<std::shared_ptr<Tile>, std::shared_ptr<TileButton>> m_buttonMap;
    static std::default_random_engine m_generator;
};

#endif // MAINWINDOW_H