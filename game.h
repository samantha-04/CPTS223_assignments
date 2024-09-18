#include <string>
#include "linkedlist.cpp"
#include "array.cpp"

using namespace std;


class Game 
{
private:
    LinkedList<std::string, std::string> commandsList;  // Command/Description linked list
    Array<std::string, int> profilesArray;               // Array of player profiles
    string playerName;                              // Current player name

public:
    // Constructor
    Game(int profileCapacity);
    Game();

    void loadFiles();    
    void shuffle(string descriptions[], int size);
    void playGame(string playerName, int numQuestions);
    void endGame();

};

