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
    keyPressedV = 0;
    playerHealth = 100;
    inDuel = false ;
    doAnimForDuel = false ;
    a = new Room("a");
    b = new Room("b");
    c = new Room("c");
        c->addItem(new Item("sherif", 1, 1));
    d = new Room("d");
    e = new Room("e");
    f = new Room("f");
    g = new Room("g");
         g->addItem(new Item("finalBoss", 1, 3));
    h = new Room("h");
    i = new Room("i");
    j = new Room("j");
        j->addItem(new Item("prisoner", 1, 2));

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
    a->setExits(f, b, d, c);
    b->setExits(NULL, NULL, NULL, a);
    c->setExits(NULL, a, NULL, NULL);
    d->setExits(a, e, NULL, i);
    e->setExits(NULL, NULL, NULL, d);
    f->setExits(NULL, NULL, a, h);
    g->setExits(NULL, NULL, NULL, f);
    h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);
    j->setExits(NULL, NULL, NULL, b);

    currentRoom = a;
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
    else if (commandWord.compare("put") == 0)
    {

    }
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
    int location = currentRoom->isItemInRoom();
    if (location  < 0 )
        cout << "item is not in room" << endl;
    else{
        cout << currentRoom->longDescription() << endl;
        Item temp = currentRoom->getItem(location);
        currentRoom->removeItem(location);
        player->addItem(temp);
        Item* tempPtr = &temp;
        delete tempPtr;
        result = player->longDescription();

        inDuel = duel();
        doAnimForDuel = false;
    }


    return result ;
}
bool ZorkUL::duel(){
    srand((int)time(0));
    keyGenerated =65 + rand()%25;
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
            else{
                addResultOfDuel();
                won = false;
                doAnimForDuel = true;
            }
        }
    }
    keyPressedV = keyPressed->key();
}
string ZorkUL::getLastItem(){
    return player->getItem(player->getNumOfItems()-1);
}

void ZorkUL::addResultOfDuel(){
    for(int i = 0 ; i < player->getNumOfItems() ; i++)
    {

        string temp = player->getItem(i);
         if(temp.compare("sherif") == 0){
             if(won){
                 player->removeItem(i);
                 Item *key = new Item("prisonKey", 0, 0);
                 player->addItem(*key);
                 rooms[1]->setExits(NULL, rooms[9], NULL, rooms[0]);
             }
             else if (!won){
                 player->removeItem(i);
                 currentRoom->addItem(new Item("sherif", 1, 1));
             }

             keyGenerated = 0;
             keyPressedV = 0;

         }
         else if(temp.compare("prisoner") == 0){
             if(won){
                 player->removeItem(i);
                 Item *key = new Item("finalBossKey", 0, 1);
                 player->addItem(*key);
                 rooms[5]->setExits(NULL, rooms[6], rooms[0], rooms[7]);
             }
             else if(!won){
                 player->removeItem(i);
                 currentRoom->addItem(new Item("prisoner", 1, 2));
             }

             keyGenerated = 0;
             keyPressedV = 0;
         }
         else if(temp.compare("finalBoss") == 0){
             if(won){
                 player->removeItem(i);
                 Item *key = new Item("drink", 0, 2);
                 player->addItem(*key);
             }
             else if(!won){
                 player->removeItem(i);
                 currentRoom->addItem(new Item("finalBoss", 1, 3));
             }

             keyGenerated = 0;
             keyPressedV = 0;
         }
    }

}
string ZorkUL::getExit(){
    cout <<  currentRoom->getExit() << endl;
    return currentRoom->getExit();
}
int ZorkUL::getNumOfItemsInRoom(){
    return currentRoom->numberOfItems();
}

bool ZorkUL::getDuel(){
    return inDuel;
}

void ZorkUL::setDuel(){
    inDuel = false ;
    doAnimForDuel = true;
    if((keyGenerated != keyPressedV) ||(keyPressedV == 0)){

        won= false;
        addResultOfDuel();
        //doAnimForDuel = false;
    }
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
void ZorkUL::setPlayerHealth(int x){
    playerHealth = playerHealth - x ;
}
int ZorkUL::getPlayerHealth(){
    return playerHealth;
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

void ZorkUL::changeRoomImage(string path) {
    cout << "in zorkUL change room";
    currentRoom->changeImage(path);
}

ZorkUL::~ZorkUL() {
    for (unsigned int i = 0; i < rooms.size(); i++) {
        delete rooms[i];
    }
}
