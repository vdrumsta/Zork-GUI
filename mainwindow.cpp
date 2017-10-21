#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>

using namespace std;
#include "ZorkUL.h"

ZorkUL zorkUL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateRoomLabel();

    // Load all images
    zorkUL.loadRoomImages();

    // Display starting room image


    displayCurrentRoomImage();
}

void MainWindow::displayCurrentRoomImage() {
    ui->roomGraphicsView->setScene(zorkUL.getCurrentRoomImage());
    ui->roomGraphicsView->show();
    ui->roomGraphicsView->fitInView(ui->roomGraphicsView->scene()->sceneRect(),Qt::IgnoreAspectRatio);
}

//*
void MainWindow::showEvent(QShowEvent *) {
    cout << "show event" << endl;
    ui->roomGraphicsView->fitInView(ui->roomGraphicsView->scene()->sceneRect(),Qt::IgnoreAspectRatio);
}
//*/

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_teleportButton_clicked()
{
    Command command("teleport", "");
    zorkUL.processButton(command);
    updateRoomLabel();
}

void MainWindow::updateRoomLabel() {
    string roomDescription = zorkUL.shortDescription();
    QString qstr = QString::fromStdString(roomDescription);
    ui->roomDescription->setText(qstr);
}
void MainWindow::on_northButton_clicked()
{
    Command command("go", "north");
    zorkUL.processButton(command);
    updateRoomLabel();
    displayCurrentRoomImage();
}
void MainWindow::on_westButton_clicked()
{
    Command command("go", "west");
    zorkUL.processButton(command);
    updateRoomLabel();
    displayCurrentRoomImage();
}

void MainWindow::on_southButton_clicked()
{
    Command command("go", "south");
    zorkUL.processButton(command);
    updateRoomLabel();
    displayCurrentRoomImage();
}

void MainWindow::on_eastButton_clicked()
{
    Command command("go", "east");
    zorkUL.processButton(command);
    updateRoomLabel();
    displayCurrentRoomImage();
}
