//#include "Vertex.h"
#include <queue>
#include "user.h"

class Van {
private:
    int id;
    int maxCapacity;
    int currentLoad;
    //vector<vector<Vertex*> > paths;
    std::queue<User*> users;

public:
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

