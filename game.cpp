#include "game.h"

//defualt constructor
Game::Game() : profilesArray(10) //default capacity of 10
{
    srand(static_cast<unsigned int>(time(0))); //seed for shuffling
}

//constructor
Game::Game(int profileCapacity) : profilesArray(profileCapacity) 
{

}

//load files
void Game::loadFiles()
{
    commandsList.loadCommands("commands.csv", commandsList);
    profilesArray.loadProfiles("profiles.csv");
}

//shuffle the descriptions (used during gameplay for randomizing the order of the descriptions)
void Game::shuffle(string descriptions[], int size) 
{
   
    for (int i = size - 1; i > 0; --i) {
        //generate a random index between 0 and i
        int randomIndex = rand() % (i + 1);

        //swap the current element with the randomly chosen one
        swap(descriptions[i], descriptions[randomIndex]);
    }
}

//main gameplay function. Gives user options to choose correct discriptiona and modifies points
void Game::playGame(string playerName, int numQuestions)
{

    for (int i = 0; i < numQuestions; ++i) 
    {
        string command = commandsList.getRandomCommand();  //get a random command
        string correctDescription = commandsList.searchCommand(command);  // Get correct description

        //array for 3 descriptions (1 correct, 2 incorrect)
        string descriptions[3];

        //add the correct description to array
        descriptions[0] = correctDescription;

        //generating 2 random incorrect descriptions from list
        int j = 1; //start at index 1 since index 0 is the correct description
        while (j < 3) 
        {
            string randomDescription = commandsList.getRandomDescription();  //get a random incorrect description
            if (randomDescription != correctDescription) //make sure it is not the correct description
            {
                descriptions[j] = randomDescription;
                j++;
            }
        }

        //shuffle the array of descriptions
        shuffle(descriptions, 3);

        //display the command and shuffled descriptions
        cout << "Command: " << command << endl;
        for (int k = 0; k < 3; k++) 
        {
            cout << k + 1 << ". " << descriptions[k] << endl;
        }

        //player chooses answer
        int choice;
        cout << "Choose the correct description (1-3): ";
        cin >> choice;

        //check if the answer is correct
        if (descriptions[choice - 1] == correctDescription) 
        {
            cout << "Correct!" << endl;
            profilesArray.updatePoints(playerName, 1);  //add 1 point
        } 
        else 
        {
            cout << "Incorrect!" << endl;
            profilesArray.updatePoints(playerName, -1);  //subtract 1 point
        }
    
    }
}

void Game::endGame()
{
    cout << "Saving your progress..." << endl;
    profilesArray.saveProfiles("profiles.csv");
    cout << "Your progress has been saved." << endl;
}
