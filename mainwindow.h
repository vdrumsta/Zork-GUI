#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>

using namespace std;


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
    void stopCombatScene();
    void on_northButton_clicked();

    void on_teleportButton_clicked();

    void on_westButton_clicked();

    void on_southButton_clicked();

    void on_eastButton_clicked();


    void on_take_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsTextItem *combatText;
    QGraphicsPixmapItem *cowboy1Item;
    QGraphicsPixmapItem *cowboy2Item;
    QGraphicsScene *combatScene;
    bool duelStarted;
    void showEvent(QShowEvent *);
    void changeCombatText(QString);
    void buildCombatScene();
    void startCombatScene();
    void cowboyShoot(int);
    void displayCurrentRoomImage();
    void updateRoomLabel();
    void updatePlaverInventLabel();
    //bool eventFilter(QObject* obj, QEvent* event);
    void keyPressEvent(QKeyEvent* e);

};

#endif // MAINWINDOW_H
