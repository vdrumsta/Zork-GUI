#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>

using namespace std;
#include "ZorkUL.h"

ZorkUL temp;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateRoomLabel();

    QGraphicsScene* roomScene = new QGraphicsScene();
    QString fileName = QString::fromStdString("C:\\Users\\vdrum\\OneDrive\\workarea\\programming\\2017\\Qt\\ZorkLab3\\images\\WildWest8bit.png");
    QImage roomImage(fileName);
    QGraphicsPixmapItem* roomImageItem = new QGraphicsPixmapItem(QPixmap::fromImage(roomImage));
    roomScene->addItem(roomImageItem);
    ui->roomGraphicsView->setScene(roomScene);
    ui->roomGraphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_northButton_clicked()
{
    Command command("go", "north");
    temp.processButton(command);
    updateRoomLabel();
}

void MainWindow::on_teleportButton_clicked()
{
    Command command("teleport", "");
    temp.processButton(command);
    updateRoomLabel();
}

void MainWindow::updateRoomLabel() {
    string roomDescription = "room = " + temp.shortDescription();
    QString qstr = QString::fromStdString(roomDescription);
    ui->roomDescription->setText(qstr);
}
