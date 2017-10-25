#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
	string description;
	string longDescription;
    int type;
    int roomKey;


public:
    Item (string description, int inWeight, float inValue);
    Item (string description);
	string getShortDescription();
    string getLongDescription();
    int getType();
	void setWeight(int weightGrams);
    int getRoomKey();
	void setValue(float value);
	int getWeaponCheck();
	void setWeaponCheck(int weaponCheck);
};

#endif /*ITEM_H_*/
