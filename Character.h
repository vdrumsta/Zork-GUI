#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "item.h"
#include <string>
#include <vector>


using namespace std;
using std::vector;


class Character {
private:
	string description;
    vector < string > itemsInCharacter;
public:
    void addItem(Item item);
    void removeItem(int x);
	Character(string description);
	string shortDescription();
	string longDescription();
    string getItem(int x);
    int getNumOfItems();

};

#endif /*CHARACTER_H_*/
