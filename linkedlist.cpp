#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "linkedlist.h"

using namespace std;

//constructor
template <typename t, typename d>
LinkedList<t,d>::LinkedList()
{
    head = nullptr;
    size = 0;

}

//destructor 
template <typename t, typename d>
LinkedList<t,d>::~LinkedList()
{
    Node* current = head;

    while (current) 
    {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

template <typename t, typename d>
void LinkedList<t,d>:: loadCommands(const string& filename, LinkedList<string, string>& commandsList)
{
    ifstream file("commands.csv"); //opening the file

    if(!file.is_open()) //checking to ensure file is able to open
    {
        cerr << "Could not open commands.csv" << endl;
        return;
    }

    string line, command, description;

    //parsing each line
    while (getline(file, line))
    {
        std::stringstream ss(line); 

        if(getline(ss, command, ',')) //parse command
        {
            if (getline(ss, description)) //parse description
            {
                commandsList.insertAtFront(command, description); //insert the command at front of linked list
            }
        }
    }

    file.close(); //closing file

}

template <typename t, typename d>
int LinkedList<t,d>::getSize()
{
    return size; //size of list
}

template <typename t, typename d>
void LinkedList<t,d>::insertAtFront(t command, d description)
{
    Node* newNode = new Node(command, description);  //new node
    newNode->next = head;  
    head = newNode;  //update head to new node
    size++;  //increase size of list
    return;
}

template <typename t, typename d>
bool LinkedList<t,d>::removeNode(t command)
{

    if (!head) return false;  //if the list is empty, nothing to remove

    //if the head is the node to remove
    if (head->command == command) 
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }

    //traverse the list to find the node to remove
    Node* current = head;
    while (current->next && current->next->command != command) 
    {
        current = current->next;
    }

    if (!current->next) 
    {
        return false;  //command not found
    }

    //remove the node
    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
    size--;
    return true;

}

template<typename t, typename d>
d LinkedList<t,d>::searchCommand(t command)
{
Node* current = head;

    while (current) 
    {
        if (current->command == command) 
        {
            return current->description; //return the description if found
        }
        current = current->next;
    }

    return ""; 
}

template<typename t, typename d>
t LinkedList<t, d>::getRandomCommand() 
{
    if (isEmpty()) 
    {
        std::cerr << "Error: Linked list is empty. Cannot retrieve a random command." << std::endl;
        return t();  //return a default value if empty
    }

    int randomIndex = rand() % size;  // Get a random index
    Node* current = head;

    for (int i = 0; i < randomIndex; ++i) 
    {
        if (current == nullptr) 
        {
            std::cerr << "Error: Invalid node traversal. Node is null." << std::endl;
            return t();  //return a default value if traversal fails
        }
        current = current->next;
    }

    if (current == nullptr) 
    {
        std::cerr << "Error: Current node is null after traversal." << std::endl;
        return t();  //handle case where node is null
    }

    return current->command;  //return the command at the random index
}



template<typename t, typename d>
d LinkedList<t, d>::getRandomDescription() 
{
    int randomIndex = rand() % size;
    Node* current = head;
    for (int i = 0; i < randomIndex; ++i) 
    {
        current = current->next;
    }
    return current->description;
}

template <typename t, typename d>
void LinkedList<t, d>::saveCommandsToFile(const std::string &filename)
{
    std::ofstream file(filename);

    if (!file.is_open()) 
    {
        std::cerr << "Error: Could not open " << filename << " for writing." << std::endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) 
    {
        file << current->command << "," << current->description << std::endl;  //write the command and description to the file
        current = current->next;
    }

    file.close();  //close file
}
