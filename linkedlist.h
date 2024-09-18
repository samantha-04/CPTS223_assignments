#include <fstream>
#include <iostream>

using namespace std;

template <typename t, typename d>
class LinkedList 
{
private:

struct Node 
{
    t command;
    d description;
    Node* next;

    Node(t command, d description)
    {
        this->command = command;
        this->description = description;
        this->next = next;
    }
};

Node* head;  // Pointer to the head of the list
int size;    // Size of the list

public:
    LinkedList(); //constuctor
    ~LinkedList(); //destructor

    void loadCommands(const string& filename,LinkedList<string, string>& commandsList);
    void insertAtFront(t command, d description);  // Insert node at the front
    bool removeNode(t command);  // Remove a node by command
    d searchCommand(t command);  // Search for a command and return description
    int getSize(); // Return the size of the list
    t getRandomCommand();
    d getRandomDescription();
    void saveCommandsToFile(const std::string& filename);

    bool isEmpty() const 
    {
        return head == nullptr;
    }
  
};