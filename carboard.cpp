/**
 *      I begun my implentation by beginning with the main class as it was the beginning of the application. After
 *      main() I begun implementing the classes and started with Player as it was the lowest level class, containing 
 *      only references to Helper. Following my way up through Board and then finally Game to complete the program.
 *      I created additional methods in Board and for main() to provide code clarity.
 *      I encountered a few issues whilst completing the assingment. I was struggling to find a way to accept inputs
 *      such as "generate  15    ,   0.3" or "init 8,   9" where there was whitespace between the parameters of the
 *      commands. As I was using the splitString() method provided in Helper in cases like this it would split the
 *      first example into ("generate", "15", ",", "0.3"). I was overcomplicating the method to handle the parameters
 *      by trying to trim the "15    ,   0.3" section all together instead of using what splitString outputted.
 *      I then found a much easier method that involved concatenating the parameters and comma together into a string
 *      with no whitespace.
 *      The helper functions included use abstract variable names which makes understanding the methods included
 *      quite difficult when looking through line by line. Additionally some of the comments provided to explain what
 *      each method should do could have been explained clearer.
 * 
*/

#include "game.h"
#include "helper.h"
#include "player.h"

using std::string;

#define OPTION_PLAY "1"
#define OPTION_INFO "2"
#define OPTION_QUIT "3"

void showStudentInformation(string name, string id, string email){
    std::cout << "--------------------\n";
    std::cout << "Name: "<< name <<"\n";
    std::cout << "No: "<< id <<"\n";
    std::cout << "Email: "<< email <<"\n";
    std::cout << "--------------------\n";
}
void mainMenuWelcome() {
    std::cout << "\nWelcome to Car Board\n";
    std::cout << "--------------------\n";
    std::cout << "1. Play game\n";
    std::cout << "2. Show student's information\n";
    std::cout << "3. Quit\n\n";

    std::cout << "Please enter you choice: ";
}
void mainMenuCommands() {
    std::cout << "You can use the following commands to play the game:\n";
    std::cout << "load <g>\n";
    std::cout << "   g: number of the game board to load\n";
    std::cout << "generate <d>,<p>\n";
    std::cout << "   d: the dimension of the game board to be generated\n";
    std::cout << "   p: the probability of the blocks on board to be generated randomly\n";
    std::cout << "init <x>,<y>,<direction>\n";
    std::cout << "   x: horizontal position of the car on the board (between 0 & 9)\n";
    std::cout << "   y: vertical position of the car on the board (between 0 & 9)\n";
    std::cout << "   direction: direction of the car's movement (north, east, south, west)\n";
    std::cout << "forward (or f)\n";
    std::cout << "turn_left (or l)\n";
    std::cout << "turn_right (or r)\n";
    std::cout << "quit\n";
}

bool mainMenu(){

    bool loopTest = true;
    bool continueProgram = true;
    string inputWord{};
    while(loopTest) {

        if (!std::cin) {
            continueProgram = false;
            loopTest = false;
        }
        
        mainMenuWelcome();

        std::getline(std::cin >> std::ws, inputWord);
        std::cout << "\n";

        if (!std::cin) {
            continueProgram = false;
            loopTest = false;
        }
        
        if (inputWord == OPTION_PLAY) {
            mainMenuCommands();

            continueProgram = true;
            loopTest = false;
        }

        if (inputWord == OPTION_INFO) {
            showStudentInformation("Kayde Page", "s3718833", "s3718833@student.rmit.edu.au");
        }

        if (inputWord == OPTION_QUIT) {
            continueProgram = false;
            loopTest = false;
        }
    }

    return continueProgram;


    
}

int main()
{   
    bool loopTest{true};
    while(loopTest) {
        if (mainMenu()) {
            Game* game = new Game();
            (*game).start();
            delete game;
        }   
        else {
            std::cout << "\nGood bye!\n\n";
            loopTest = false;
        }
    }
    return EXIT_SUCCESS;
}
