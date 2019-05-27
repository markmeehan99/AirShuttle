#include "Van.h"

Van::Van(int id, int cap)
{
    this->id = id;
    maxCapacity = cap;
    currentLoad = 0;
}

int Van::getId()
{
    return this->id;
}

int Van::getCurrentLoad()
{
    return this->currentLoad;
}

void Van::decreaseLoad()
{
    this->currentLoad--;
}
void Van::increaseLoad()
{
    this->currentLoad++;
}

int Van::getMaxCapacity()
{
    return this->maxCapacity;
}

bool Van::isVanEmpty()
{
    return currentLoad == 0;
}

void Van::pushUser(User *user) {
    //users.push_back(user);
    this->increaseLoad();
}

void Van::popUser() {
    //users.pop();
    this->decreaseLoad();
}

User* Van::nextUser() {
    return users.front();
}
