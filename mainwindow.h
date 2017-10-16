#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_northButton_clicked();

    void on_teleportButton_clicked();

private:
    Ui::MainWindow *ui;
    void updateRoomLabel();
};

#endif // MAINWINDOW_H
