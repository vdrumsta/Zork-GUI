#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Character.h"
#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
//#include "keypressreceiver.h"
#include <iostream>
#include <string>
#include <vector>
#include <QCoreApplication>
using namespace std;

class ZorkUL {
private:
	Parser parser;
    int keyPressedV ;
    int playerHealth;
    Room *currentRoom;
    Character *player ;
    vector<Room*> rooms;
    bool won ;
    bool doAnimForDuel ;
    bool inDuel;
    int timerID;
    int keyGenerated;
	void createRooms();
    void createPlayer();
	void printWelcome();
	bool processCommand(Command command);
    bool duel();
	void printHelp();
	void goRoom(Command command);
    void createItems();
    void displayItems();
    void teleportRandomRoom();
    void addResultOfDuel();


public:
	ZorkUL();
    void loadRoomImages();
    void generateKey();
    void setDuel();
    int getKeyGen();
    bool getAnimForDuel();
    bool getWon();
    QGraphicsScene* getCurrentRoomImage();
    void play();
    void setKeyPressed(QKeyEvent* keyPressed);
    string takeItem();
    string getInventory();
    void processButton(Command command);
    string shortDescription();
	string go(string direction);
    bool getDuel();
    string getLastItem();
    string getExit();
    int getNumOfItemsInRoom();
    void setPlayerHealth(int x);
    int getPlayerHealth();
    void changeRoomImage(string);

};

#endif /*ZORKUL_H_*/
