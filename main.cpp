/*
ADVANTAGES/DISADVANTAGES LINKED LIST
One advantage of using a linked list for storing the commands/descriptions is that it's dynamic!
Unlike an array, you aren't limited by a fixed number.

One disadvantage of using a linked list is that it has a slower acces time than an array (O(n)).
This is because you have to traverse the list to find the element you want to access, so it 
can be a bit inefficent. 

ADVANTAGES/DISADVANTAGES ARRAY
One advantage of using an array for profile storage is 
that it allows for constant-time access of elements by their index, which
makes it efficient when you know the index of the element you want to access.

One disadvantage of using an array for profile storage is that it has a fixed size,
which can limit the number of profiles you store. You can resize, but this gets complicated
and can use up time and memory.
*/

#include <iostream>
#include <string>
#include "game.cpp"

using namespace std;


int main()
{

    //variables 
    string userName;
    int selection;
    LinkedList<string, string> list;
    Array<string, int> array(10); 
    Game game;

    //loading files from the game class (want to do this before the user selects an option 
    //in case they choose to just add/remove commands)
    game.loadFiles();

    while (true)
    {
        cout << "Please select an option listed below:\n";
        cout << "1. Game Rules\n2. Play Game\n3. Load Previous Game\n4. Add Command\n5. Remove Command\n6. Exit\n";
        cout << "Your selection: ";
        cin >> selection;     

        if (cin.fail()) // the input is not an integer
        {
            cout << "Your selection is invalid. Please select again." << endl;
            cout << "=============================================================================" << endl << endl;
            cin.clear();
            cin.ignore();
        }
        else
        {
            switch (selection)
            {
                case 1: // Game Rules
                {
                    cout << "================================= Game Rule ===================================" << endl;
                    cout << "To play the game, select \"2\" where you will be prompted for your name and number of questions.\n";
                    cout << "Each question presents a specific Linux command where you will be able to choose from 3 different options. Each correct answer yields a point.\n";
                    cout << "You can also add and delete commands as needed.\n";
                    cout << "================================= Game Rule ===================================" << endl << endl;

                    break;
                }

                case 2: case 3: // 2. Play Game; 3. Load Previous Game
                {
                    cout << "Please enter your name: ";
                    cin >> userName;
                    
                    if (selection == 3)
                    {
                        array.findProfile(userName); //find the profile for prev games
                    }
                    else
                    {
                        array.addProfile(userName, 0); //add a new profile for new games
                    }

                    cout << "Please enter the number of questions you would like to answer: ";
                    int numQuestions;
                    cin >> numQuestions;

                    game.playGame(userName, numQuestions); //play the game

                    break;
                }

                case 4: // Add Command
                {
                    string newCommandToAdd, newDescriptionToAdd;
                    cout << "To add a command to the library, please enter the command name that you would add: " << endl;
                    cin.ignore(); //clear the buffer
                    getline(cin, newCommandToAdd); //use getline in case the command has spaces

                    cout << "Next, enter the description for the new command: " << endl;
                    getline(cin, newDescriptionToAdd); //use getline in case the description has spaces

                    list.insertAtFront(newCommandToAdd, newDescriptionToAdd);
                    
                    cout << "............." << endl; 
                    cout << "Your command has been added." << endl;
                    break;
                }

                case 5: // Remove Command
                {
                    string commandToDelete;
                    cout << "Please enter the name of the command that you would remove: ";
                    cin.ignore(); //clear the buffer
                    getline(cin, commandToDelete); //use getline in case the command has spaces

                    if (list.removeNode(commandToDelete)) //if the command was found and removed
                    {
                        cout << "............." << endl;
                        cout << "The command has been removed." << endl;
                    }
                    else //command not in list
                    {
                        cout << "............." << endl; 
                        cout << "The command was not found." << endl;
                    }
                    
                    break;
                }
                    
                case 6: // Exit
                {
                    game.endGame(); //save the profiles
                    return 0;
                }


            } // end of switch(selection)
        } // end of else: check (cin.fail())
        
    } // end of while(true)
} // end of int main()


