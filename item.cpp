#include "item.h"

Item::Item (string inDescription, int aType, float aRoomKey/**, int weaponCheck*/) {
	description = inDescription;
    type = aType;
    roomKey =aRoomKey;
}

Item::Item(string inDescription) {
	description = inDescription;
}

string Item::getShortDescription()
{
	return description;
}
int Item::getType()
{
    return type;
}
int Item::getRoomKey()
{
    return roomKey ;
}
string Item::getLongDescription()
{
	return " item(s), " + description + ".\n";
}

