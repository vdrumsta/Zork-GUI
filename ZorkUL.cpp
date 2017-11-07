#include <QKeyEvent>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>


using namespace std;
#include "ZorkUL.h"

ZorkUL::ZorkUL() {
	createRooms();
    createPlayer();
}

void ZorkUL::createRooms()  {
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
    keyGenerated = 0 ;
    inDuel = false ;
    doAnimForDuel = false ;
    a = new Room("a");
      //  a->addItem(new Item("x", 1, 11));
      //  a->addItem(new Item("y", 2, 22));
    b = new Room("b");
        b->addItem(new Item("prisoner", 1, 2));
        //b->addItem(new Item("tavernkey", 1,1));
    c = new Room("c");
        c->addItem(new Item("sherif", 1, 1));
    d = new Room("d");
    e = new Room("e");
    f = new Room("f");
    g = new Room("g");
    h = new Room("h");
    i = new Room("i");
    j = new Room("j");

    rooms.push_back(a);//0
    rooms.push_back(b);//1
    rooms.push_back(c);//2
    rooms.push_back(d);//3
    rooms.push_back(e);//4
    rooms.push_back(f);//5
    rooms.push_back(g);//6
    rooms.push_back(h);//7
    rooms.push_back(i);//8
    rooms.push_back(j);//9

//             (N, E, S, W)
    a->setExits(f, NULL, d, c);
    b->setExits(NULL, j, NULL, a);
    c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, g, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);
    j->setExits(NULL, NULL, NULL, b);

        currentRoom = a;
    Character *player  = new Character("player1");
}
void ZorkUL::createPlayer(){
     player  = new Character("player1");
}

QGraphicsScene* ZorkUL::getCurrentRoomImage() {
    return currentRoom->getRoomImage();
}

void ZorkUL::loadRoomImages() {
    for (unsigned int i = 0; i < rooms.size(); i++) {
        rooms[i]->loadImage();
    }
}

string ZorkUL::shortDescription() {
    string temp = currentRoom->longDescription();
    if(inDuel)
        temp += "true";
    else
        temp += "false";
    return temp ;
}

void ZorkUL::processButton(Command command) {
    processCommand(command);
}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
	printWelcome();

	// Enter the main command loop.  Here we repeatedly read commands and
	// execute them until the ZorkUL game is over.

	bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
	}
    cout << endl;
    cout << "end" << endl;
}

void ZorkUL::printWelcome() {
    cout << "start"<< endl;
    cout << "info for help"<< endl;
    cout << endl;
    cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool ZorkUL::processCommand(Command command) {
	if (command.isUnknown()) {
        cout << "invalid input"<< endl;
		return false;
	}

	string commandWord = command.getCommandWord();
	if (commandWord.compare("info") == 0)
		printHelp();

	else if (commandWord.compare("map") == 0)
		{
        cout << "[h] --- [f] --- [g]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[c] --- [a] --- [b] --- [j]" << endl;
        cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[i] --- [d] --- [e]" << endl;
		}

	else if (commandWord.compare("go") == 0)
		goRoom(command);
    else if (commandWord.compare("teleport") == 0) {
        cout << "goes into teleport";
        teleportRandomRoom();
    }
    /*else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            cout << "item is not in room" << endl;
        else
            cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;
            Item temp = currentRoom->getItem(location);
            currentRoom->removeItem(location);
            player->addItem(temp);
            player->longDescription();

        }
    }*/

    else if (commandWord.compare("put") == 0)
    {

    }
    /*
    {
    if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
    else if (commandWord.compare("quit") == 0) {
		if (command.hasSecondWord())
            cout << "overdefined input"<< endl;
		else
			return true; /**signal to quit*/
	}
	return false;
}
string ZorkUL::takeItem(){
    string result = "";
    //cout << "you're trying to take prisonKey" << endl;
    int location = currentRoom->isItemInRoom();
    if (location  < 0 )
        cout << "item is not in room" << endl;
    else{

        cout << "item is in room" << endl;
        cout << "index number " << + location << endl;
        cout << endl;
        cout << currentRoom->longDescription() << endl;
        Item temp = currentRoom->getItem(location);
        currentRoom->removeItem(location);
        player->addItem(temp);
        result = player->longDescription();

        if(temp.getType() == 1){

            if(temp.getShortDescription().compare("sherif") == 0){
                inDuel = duel();
                if(won)
                    currentRoom->addItem(new Item("prisonKey", 1, 0));
            }

        }
        else{
            if(temp.getShortDescription().compare("prisonKey") == 0){
                rooms[0]->setExits(rooms[5], rooms[1], rooms[3], rooms[2]);
            }
            else if(temp.getShortDescription().compare("tavernKey")){
               // rooms[0]->setExits(rooms[5], rooms[1], rooms[3], rooms[2]);
            }
            else if(temp.getShortDescription().compare("drink")){
               // rooms[0]->setExits(rooms[5], rooms[1], rooms[3], rooms[2]);
            }
        }


    }
    /*int num = player->getNumOfItems();
    for(int i = 0 ; i < num ; i++){
         if(player->getItem(i).compare("prisonKey") == 0){
             rooms[0]->setExits(rooms[5], rooms[1], rooms[3], rooms[2]);
         }
    }*/

    return result ;
}
bool ZorkUL::duel(){
    srand((int)time(0));
    keyGenerated =65 + rand()%25;
    cout << keyGenerated << endl;
    return true;
}

void ZorkUL::setKeyPressed(QKeyEvent* keyPressed){
    if(inDuel){
        if(keyGenerated != 0){
            if(keyPressed->key() == keyGenerated){
                won = true;
                doAnimForDuel = true;
                addResultOfDuel();
            }
        }
    }
    int x = keyPressed->key();
    cout << x << endl;
}
void ZorkUL::addResultOfDuel(){
    for(int i = 0 ; i < player->getNumOfItems() ; i++)
    {
        Item temp = player->getItem(i);
         if(temp.getShortDescription().compare("sherif") == 0){
             currentRoom->addItem(new Item("prisonKey", 0, 0));
             player->removeItem(i);
         }
         else if(temp.getShortDescription().compare("prisoner") == 0){
             currentRoom->addItem(new Item("finalBossKey", 0, 1));
             player->removeItem(i);
         }
         else if(temp.getShortDescription().compare("finalBoss") == 0){
             currentRoom->addItem(new Item("drink", 0, 2));
             player->removeItem(i);
         }
    }

}

void ZorkUL::setDuel(){
    inDuel = false ;
    doAnimForDuel = true;
}

int ZorkUL::getKeyGen(){
    return keyGenerated;
}
bool ZorkUL::getAnimForDuel(){
    return doAnimForDuel ;
}
bool ZorkUL::getWon(){
    return won ;
}

void ZorkUL::generateKey(){

    keyGenerated = (rand()%25)+65;

}

bool ZorkUL::getDuel() {
    return inDuel;
}

string ZorkUL::getInventory(){
   return player->longDescription();
}

/** COMMANDS **/
void ZorkUL::printHelp() {
    cout << "valid inputs are; " << endl;
	parser.showCommands();

}

void ZorkUL::teleportRandomRoom() {
    int randomRoom = rand() % rooms.size();
    currentRoom = rooms[randomRoom];
    //cout << currentRoom->longDescription() << endl;
}

void ZorkUL::goRoom(Command command) {
	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
        cout << "underdefined input"<< endl;
	else {
		currentRoom = nextRoom;
        cout << currentRoom->longDescription() << endl;
	}
}

string ZorkUL::go(string direction) {
	//Make the direction lowercase
	//transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
	//Move to the next room
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}
