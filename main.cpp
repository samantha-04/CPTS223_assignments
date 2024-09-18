/*
ADVANTAGES/DISADVANTAGES LINKED LIST

ADVANTAGES/DISADVANTAGES ARRAY
*/

#include <iostream>
#include <string>
#include "game.cpp"

using namespace std;


int main()
{

    string userName;
    int selection;
    LinkedList<string, string> list;
    Array<string, int> array(10); // Assuming the constructor takes an integer parameter for size
    Game game;

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
                        array.findProfile(userName);
                    }
                    else
                    {
                        array.addProfile(userName, 0);
                    }

                    cout << "Please enter the number of questions you would like to answer: ";
                    int numQuestions;
                    cin >> numQuestions;

                    game.playGame(userName, numQuestions);

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

                    if (list.removeNode(commandToDelete))
                    {
                        cout << "............." << endl;
                        cout << "The command has been removed." << endl;
                    }
                    else
                    {
                        cout << "............." << endl;
                        cout << "The command was not found." << endl;
                    }
                    
                    break;
                }
                    
                case 6: // Exit
                {
                    game.endGame();
                    return 0;
                }


            } // end of switch(selection)
        } // end of else: check (cin.fail())
        
    } // end of while(true)
} // end of int main()


