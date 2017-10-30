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
     void updateUI();
    void setDuel();
    void showKey();
    void on_northButton_clicked();

    void on_teleportButton_clicked();

    void on_westButton_clicked();

    void on_southButton_clicked();

    void on_eastButton_clicked();


    void on_take_clicked();

private:
    Ui::MainWindow *ui;
    void showEvent(QShowEvent *);
    void displayCurrentRoomImage();
    void updateRoomLabel();
    void updatePlaverInventLabel();
    //bool eventFilter(QObject* obj, QEvent* event);
    void keyPressEvent(QKeyEvent* e);

};

#endif // MAINWINDOW_H
