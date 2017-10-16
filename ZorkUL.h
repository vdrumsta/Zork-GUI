#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ZorkUL {
private:
	Parser parser;
    Room *currentRoom;
    vector<Room*> rooms;
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();
	void goRoom(Command command);
    void createItems();
    void displayItems();
    void teleportRandomRoom();

public:
	ZorkUL();
    void play();
    void processButton(Command command);
    string shortDescription();
	string go(string direction);
};

#endif /*ZORKUL_H_*/
