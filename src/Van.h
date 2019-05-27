//#include "Vertex.h"
#include <queue>
#include "user.h"

class Van {
private:
    int id;
    int maxCapacity;
    int currentLoad;

public:
    std::vector<User*> users;
    Van(int id, int cap=10);
    int getId();
    int getCurrentLoad();
    void decreaseLoad();
    void increaseLoad();
    int getMaxCapacity();

    bool isVanEmpty();

    void pushUser(User *user);
    void popUser();
    User* nextUser();
};

