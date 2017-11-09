#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>
#include <QFontDatabase>
#include <sstream>

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
    ui->take->setIcon(QIcon("../ZorkGUIProject/images/duel.png"));
    ui->take->setIconSize(QSize(50,50));
    ui->playerInventory->setText("Player inventory");
     ui->healthBar->setValue(100);
    changedRoom();




    // Display an image on combat view
    combatScene = new QGraphicsScene(this);
    ui->combatGraphicsView->setScene(combatScene);
    buildCombatScene();

    duelStarted = false;


    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateUI()));

    timer->start(1000);

}
void MainWindow::updateUI(){
    updateRoomLabel();
    ui->healthBar->setValue(zorkUL.getPlayerHealth());
    //updatePlaverInventLabel();
    if(zorkUL.getNumOfItemsInRoom())
        ui->take->setEnabled(true);
    if(zorkUL.getKeyGen() > 0 && !duelStarted){
        changeCombatText(QString::fromStdString("Get ready to draw!"));
        startCombatScene();
        duelStarted = true;

        QTimer::singleShot(5000, this,SLOT(showKey()));
        QTimer::singleShot(7000, this,SLOT(setDuel()));

    }
    if(zorkUL.getAnimForDuel() && duelStarted){
        if(zorkUL.getWon()){
            cowboyShoot(1);
            changeCombatText(QString::fromStdString("You won!"));
            if(zorkUL.getLastItem().compare("prisonKey")==0) {
                 ui->Items->addItem(QIcon("../ZorkGUIProject/images/prisonKey1.png"),"Prison Key");
                 zorkUL.changeRoomImage("../ZorkGUIProject/images/cCleared.png");
            }
            else if(zorkUL.getLastItem().compare("finalBossKey")==0) {
                ui->Items->addItem(QIcon("../ZorkGUIProject/images/barKey.png"),"Bar Key");
            }
            else if(zorkUL.getLastItem().compare("drink")==0) {
                ui->Items->addItem(QIcon("../ZorkGUIProject/images/whiskey.png"),"Drink");
                QTimer::singleShot(1000 , this,SLOT(gameOverWin()));
            }
        }
        else {
            cowboyShoot(2);
            changeCombatText(QString::fromStdString("You lost!"));
            zorkUL.setPlayerHealth(20);
            if (zorkUL.getPlayerHealth() <= 0) {
                QTimer::singleShot(1000 , this,SLOT(gameOverLose()));
            }
        }
        duelStarted = false;
        QTimer::singleShot(1000, this,SLOT(stopCombatScene()));
    }
}

void MainWindow::gameOverLose() {
    string gameOverImgPath = "../ZorkGUIProject/images/gameOverLose.png";
    QImage gameOverImage(QString::fromStdString(gameOverImgPath));
    backgroundItem->setPixmap(QPixmap::fromImage(gameOverImage));
}

void MainWindow::gameOverWin() {
    string gameOverImgPath = "../ZorkGUIProject/images/gameOverWin.png";;
    QImage gameOverImage(QString::fromStdString(gameOverImgPath));
    backgroundItem->setPixmap(QPixmap::fromImage(gameOverImage));
}

void MainWindow::changedRoom(){
    string s = zorkUL.getExit();
       istringstream iss(s);
     ui->northButton->setDisabled(true);
     ui->eastButton->setDisabled(true);
     ui->southButton->setDisabled(true);
     ui->westButton->setDisabled(true);
     ui->take->setDisabled(true);
     if(zorkUL.getNumOfItemsInRoom())
         ui->take->setEnabled(true);

       do
       {
           string subs;
           iss >> subs;

            if(subs.compare("north")== 0)
                ui->northButton->setEnabled(true);
            /*else
                ui->northButton->setDisabled(true);*/
            if(subs.compare("east")== 0)
                ui->eastButton->setEnabled(true);
          /*  else
                ui->eastButton->setDisabled(true);*/
            if(subs.compare("south")== 0)
                ui->southButton->setEnabled(true);
            /*else
                ui->southButton->setDisabled(true);*/
            if(subs.compare("west")== 0)
                ui->westButton->setEnabled(true);
           /* else
                ui->westButton->setDisabled(true);*/
       } while (iss);
}

void MainWindow::buildCombatScene() {
    string backgroundImgPath = "../ZorkGUIProject/images/combat.png";
    QImage backgroundQImage(QString::fromStdString(backgroundImgPath));
    backgroundItem = combatScene->addPixmap(QPixmap::fromImage(backgroundQImage));

    // Create combat text
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

    // Add cowboys
    string cowboyImgPath = "../ZorkGUIProject/images/cowboy1.png";
    QImage cowboyQImage(QString::fromStdString(cowboyImgPath));

    cowboy1Item = combatScene->addPixmap(QPixmap::fromImage(cowboyQImage));
    cowboy2Item = combatScene->addPixmap(QPixmap::fromImage(cowboyQImage));

    cowboy1Item->setPos(50, 50);
    cowboy2Item->moveBy(ui->combatGraphicsView->width() - 75, 50);

    cowboy1Item->hide();
    cowboy2Item->hide();
}

void MainWindow::startCombatScene() {
    string cowboy1ImgPath = "../ZorkGUIProject/images/cowboy1.png";
    string cowboy2ImgPath = "../ZorkGUIProject/images/cowboy2.png";
    QImage cowboy1QImage(QString::fromStdString(cowboy1ImgPath));
    QImage cowboy2QImage(QString::fromStdString(cowboy2ImgPath));

    cowboy1Item->setPixmap(QPixmap::fromImage(cowboy1QImage));
    cowboy2Item->setPixmap(QPixmap::fromImage(cowboy2QImage));

    cowboy1Item->show();
    cowboy2Item->show();
}

void MainWindow::cowboyShoot(int cowboy) {
    if (cowboy == 1) {
        string cowboy1ImgPath = "../ZorkGUIProject/images/cowboy1shot.png";
        QImage cowboy1QImage(QString::fromStdString(cowboy1ImgPath));
        cowboy1Item->setPixmap(QPixmap::fromImage(cowboy1QImage));
    } else {
        string cowboy2ImgPath = "../ZorkGUIProject/images/cowboy2shot.png";
        QImage cowboy2QImage(QString::fromStdString(cowboy2ImgPath));
        cowboy2Item->setPixmap(QPixmap::fromImage(cowboy2QImage));
    }
}

void MainWindow::stopCombatScene() {
    cowboy1Item->hide();
    cowboy2Item->hide();
    changeCombatText(QString::fromStdString(""));
}

void MainWindow::changeCombatText(QString text) {
    combatText->setPlainText(text);

    int xPos = ui->combatGraphicsView->width() / 2;
    int yPos = ui->combatGraphicsView->height() / 8;
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
    ui->roomGraphicsView->fitInView(ui->roomGraphicsView->scene()->sceneRect(),Qt::IgnoreAspectRatio);
}
//*/

MainWindow::~MainWindow()
{
    delete ui;
}


/*  Commented out in case we need a teleport button later
void MainWindow::on_teleportButton_clicked()
{
    Command command("teleport", "");
    zorkUL.processButton(command);
    updateRoomLabel();
}
//*/

void MainWindow::updateRoomLabel() {
    string roomDescription = zorkUL.shortDescription();
    QString qstr = QString::fromStdString(roomDescription);
    //ui->roomDescription->setText(qstr);
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
    changedRoom();
}
void MainWindow::on_westButton_clicked()
{
    Command command("go", "west");
    zorkUL.processButton(command);
    updateRoomLabel();
    displayCurrentRoomImage();
    changedRoom();
}

void MainWindow::on_southButton_clicked()
{
    Command command("go", "south");
    zorkUL.processButton(command);
    updateRoomLabel();
    displayCurrentRoomImage();
    changedRoom();
}

void MainWindow::on_eastButton_clicked()
{
    Command command("go", "east");
    zorkUL.processButton(command);
    updateRoomLabel();
    displayCurrentRoomImage();
    changedRoom();
}

void MainWindow::on_take_clicked()
{
    if (zorkUL.getNumOfItemsInRoom() > 0) {
        zorkUL.takeItem();
        updateRoomLabel();
        displayCurrentRoomImage();
    }
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
