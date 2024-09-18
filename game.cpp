#include "game.h"

//defualt constructor
Game::Game() : profilesArray(10)
{
    srand(static_cast<unsigned int>(time(0))); //seed for shuffling
}


Game::Game(int profileCapacity) : profilesArray(profileCapacity)
{

}

void Game::loadFiles()
{
    commandsList.loadCommands("commands.csv", commandsList);
    profilesArray.loadProfiles("profiles.csv");
}



void Game::shuffle(string descriptions[], int size) 
{
   
    for (int i = size - 1; i > 0; --i) {
        // Generate a random index between 0 and i
        int randomIndex = rand() % (i + 1);

        // Swap the current element with the randomly chosen one
        swap(descriptions[i], descriptions[randomIndex]);
    }
}

void Game::playGame(string playerName, int numQuestions)
{

    for (int i = 0; i < numQuestions; ++i) 
    {
        std::string command = commandsList.getRandomCommand();  // Get a random command
        std::string correctDescription = commandsList.searchCommand(command);  // Get correct description

        // Define a fixed-size array for 3 descriptions (1 correct, 2 incorrect)
        std::string descriptions[3];

        // Add the correct description to the array
        descriptions[0] = correctDescription;

        // Fetch 2 random incorrect descriptions
        int index = 1;
        while (index < 3) {
            std::string randomDescription = commandsList.getRandomDescription();  // Get a random incorrect description
            if (randomDescription != correctDescription) {
                descriptions[index] = randomDescription;
                index++;
            }
        }

        // Manually shuffle the array of descriptions
        shuffle(descriptions, 3);

        // Display the command and shuffled descriptions
        std::cout << "Command: " << command << std::endl;
        for (int j = 0; j < 3; ++j) {
            std::cout << j + 1 << ". " << descriptions[j] << std::endl;
        }

        // Ask the player to choose the correct description
        int choice;
        std::cout << "Choose the correct description (1-3): ";
        std::cin >> choice;

        // Check if the answer is correct
        if (descriptions[choice - 1] == correctDescription) {
            std::cout << "Correct!" << std::endl;
            profilesArray.updatePoints(playerName, 1);  // Add 1 point
        } else {
            std::cout << "Incorrect!" << std::endl;
            profilesArray.updatePoints(playerName, -1);  // Subtract 1 point
        }
    
}

}

void Game::endGame()
{
    cout << "Saving your progress..." << endl;
    profilesArray.saveProfiles("profiles.csv");
    cout << "Your progress has been saved." << endl;
}
