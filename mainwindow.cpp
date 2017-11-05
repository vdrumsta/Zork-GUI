#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QFontDatabase>

using namespace std;
#include "ZorkUL.h"

ZorkUL zorkUL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateRoomLabel();
    setFocusPolicy(Qt::StrongFocus);

    // Load all images
    zorkUL.loadRoomImages();

    // Display starting room image
    displayCurrentRoomImage();

    // Display an image on combat view
    combatScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(combatScene);

    duelStarted = false;

    string backgroundImgPath = "../ZorkGUIProject/images/combat.png";
    QImage backgroundQImage(QString::fromStdString(backgroundImgPath));
    QGraphicsPixmapItem *backgroundItem = combatScene->addPixmap(QPixmap::fromImage(backgroundQImage));

    string cowboyImgPath = "../ZorkGUIProject/images/cowboy.png";
    QImage cowboyQImage(QString::fromStdString(cowboyImgPath));

    cowboy1Item = combatScene->addPixmap(QPixmap::fromImage(cowboyQImage));
    cowboy2Item = combatScene->addPixmap(QPixmap::fromImage(cowboyQImage));
    combatText = new QGraphicsTextItem();
    combatScene->addItem(combatText);

    // Change the font and color of combat text
    QFontDatabase::addApplicationFont("../ZorkGUIProject/fonts/arbutus.ttf");
    QFont combatTextFont;
    combatTextFont.setPointSize(25);
    combatTextFont.setFamily("arbutus");
    combatText->setFont(combatTextFont);
    QColor combatTextColor(125, 0, 0, 255);
    combatText->setDefaultTextColor(combatTextColor);

    cowboy1Item->setPos(50, 50);
    cowboy2Item->moveBy(ui->graphicsView->width() - 75, 50);

    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateUI()));

    timer->start(1000);

}
void MainWindow::updateUI(){
    updateRoomLabel();
    updatePlaverInventLabel();
    //combatText->moveBy(10,5);
    if(zorkUL.getKeyGen() > 0){
        if (!duelStarted) {
            changeCombatText(QString::fromStdString("Get ready to draw!"));
            duelStarted = true;
        }

        QTimer::singleShot(5000, this,SLOT(showKey()));
        QTimer::singleShot(7000, this,SLOT(setDuel()));

    }
    if(zorkUL.getAnimForDuel()){
        QString x = "";
        if(zorkUL.getWon()){
            changeCombatText(QString::fromStdString("You won!"));
        }
        else {
            changeCombatText(QString::fromStdString("You lost!"));
        }
    }
}

void MainWindow::changeCombatText(QString text) {
    combatText->setPlainText(text);

    int xPos = ui->graphicsView->width() / 2;
    int yPos = ui->graphicsView->height() / 2;
    combatText->setPos(xPos - combatText->boundingRect().width()/2.0, yPos);
}

void MainWindow::setDuel(){
    zorkUL.setDuel();
}
void MainWindow::showKey(){
    QChar x =  zorkUL.getKeyGen();
    QString pressString = QString::fromStdString("Press ");
    pressString += x;
    changeCombatText(pressString);
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
void MainWindow::updatePlaverInventLabel() {
    string temp = zorkUL.getInventory();
    QString qstr = QString::fromStdString(temp);
    ui->playerInventory->setText(qstr);
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

void MainWindow::on_take_clicked()
{
   // Command command("take", "prisonKey");
    //zorkUL.processButton(command);
    zorkUL.takeItem();
    updatePlaverInventLabel();
    updateRoomLabel();
    displayCurrentRoomImage();
}
/*bool MainWindow::eventFilter(QObject* obj, QEvent* event){

    if (event->type()== QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);

        zorkUL.setKeyPressed(key);

    }
    return true;
}*/
void MainWindow::keyPressEvent(QKeyEvent* e){
    zorkUL.setKeyPressed(e);
}
