#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <QString>
#include <vector>
#include <QCoreApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include "item.h"
using namespace std;
using std::vector;

class Room {

private:
    string imagePath;
    QImage* roomQImage;
    QGraphicsPixmapItem* roomImage;
    QGraphicsScene* roomScene;
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;


public:
    QGraphicsScene* getRoomImage();
    void loadImage();
    int numberOfItems();
	Room(string description);
	void setExits(Room *north, Room *east, Room *south, Room *west);
	string shortDescription();
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    int isItemInRoom();
    Item getItem(int x);
    void removeItem(int x);
    void removeItemFromRoom(int location);
    string getExit();
    void changeImage(string path);
    ~Room();
};

#endif
