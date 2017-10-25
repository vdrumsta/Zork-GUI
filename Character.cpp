#include "Character.h"

Character::Character(string description) {
	this->description = description;
}
void Character::addItem(Item &item) {
    itemsInCharacter.push_back(item.getShortDescription());
}
/*void Character::addItem(Item *item) {
    itemsInCharacter.push_back(*item);
    delete item;
}*/
string Character::longDescription()
{
  string ret = this->description;
  ret += "\n Item list:\n";
  int size = itemsInCharacter.size();

  for (int i = 0; i < size ; i++)
    ret += "\t"+ itemsInCharacter[i] + "\n";
  return ret;
}
string Character::getItem(int x){
    string temp  = "" + itemsInCharacter[x];
    return temp ;
}
int Character::getNumOfItems(){
    return itemsInCharacter.size();
}



