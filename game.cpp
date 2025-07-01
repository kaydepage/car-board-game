#include "game.h"

using std::string;

Game::Game(): board {new Board()}, player {new Player()}
{

}

Game::~Game()
{
    delete board;
    delete player;
}

/**
 * Both loadBoard() and initializePlayer() return a boolean based on their continueProgram.
 * As such, the start() method uses this to transition between game sections.
*/
void Game::start()
{
    if (this->loadBoard()) {
        if(this->initializePlayer()) {
            this->play();
        }
    }
}


bool Game::loadBoard()
{
    bool continueProgram{};
    bool loopTest{true};
    string inputWord{};
    while(loopTest) {
        std::cout << "\n";
        board->display(player);

        std::cout << "\nAt this stage of the program, only two commands are acceptable:\n";
        std::cout << "  load <g>\n";
        std::cout << "  generate <d>,<p>\n";
        std::cout << "  quit\n\n";

        
        std::getline(std::cin >> std::ws, inputWord);
        std::vector<std::string> splitString;
        Helper::splitString(inputWord, splitString, " ");

        if (!std::cin) {
            continueProgram = false;
            loopTest = false;
        }

        else if (splitString[0] == "quit") {
            continueProgram = false;
            loopTest = false;
        }
        /**
         * As all input options beyond quit require parameters such as <d>,<p> in generate,
         * a check is made to see if anything else is entered besides the 
         * command option e.g. load, generate.
        */
        else if (splitString.size() > 1) {
            if (splitString[0] == "generate") {
            //Performs a check to see whether given input produces a valid generation result
            bool generateResult = board->generateResult(splitString);
                if (generateResult == false) {
                    Helper::printInvalidInput();
                }
                else {
                    continueProgram = true;
                    loopTest = false;
                }
            }

            else if (splitString[0] == "load" && splitString[1] == "1") {
                board->load(1);
                continueProgram = true;
                loopTest = false;
                
            }
            else if (splitString[0] == "load" && splitString[1] == "2") {
                board->load(2);
                continueProgram = true;
                loopTest = false;
            }
            else {
                Helper::printInvalidInput();
            }
        }
        
        else {
            Helper::printInvalidInput();
        }
        
        
        
    }
    return continueProgram;
}

/**
 * Unlike loadBoard(), initializePlayer() will only move to play() if 
 * init is used correctly.
 * Load and generate will only for changing the board however much as 
 * desired before init is used.
*/
bool Game::initializePlayer()
{   
    string inputWord{};
    bool continueProgram{};
    bool loopTest{true};
    while(loopTest) {

        std::cout << "\n";
        board->display(player);

        std::cout << "\nAt this stage of the program, only two commands are acceptable:\n";
        std::cout << "  load <g>\n";
        std::cout << "  generate <d>,<p>\n";
        std::cout << "  init <x>,<y>,<direction>\n";
        std::cout << "  quit\n\n";

        std::getline(std::cin >> std::ws, inputWord);
        std::vector<std::string> splitString;
        Helper::splitString(inputWord, splitString, " ");

        if (!std::cin) {
            continueProgram = false;
            loopTest = false;
        }

        else if (splitString[0] == "quit") {
            continueProgram = false;
            loopTest = false;
        }

        else if (splitString.size() > 1) {

            if (splitString[0] == "init") {
                //Performs a check to see whether given input produces a valid init result
                if (board->initResult(player, splitString)) {
                    continueProgram = true;
                    loopTest = false;
                }
            }   
            
            else if (splitString[0] == "generate") {
                //Performs a check to see whether given input produces a valid generation result
                if (!board->generateResult(splitString)) {
                    Helper::printInvalidInput();
                }
            }

            else if (splitString[0] == "load" && splitString[1] == "1") {
                board->load(1); 
            }
            else if (splitString[0] == "load" && splitString[1] == "2") {
                board->load(2);
            }
            else {
                Helper::printInvalidInput();
            }
        }

        
        
        else {
            Helper::printInvalidInput();
        }
        
            

    }
    return continueProgram;
}

void Game::play()
{
    
    bool loopTest = true;
    while(loopTest) {
        board->display(player);
        std::cout << "\n";

        std::cout << "\nAt this stage of the program, only two commands are acceptable:\n";
        std::cout << "  forward (or f)\n";
        std::cout << "  turn_left (or l)\n";
        std::cout << "  turn_right (or r)\n";
        std::cout << "  quit\n\n";

        string inputWord{};
        std::getline(std::cin >> std::ws, inputWord);
        if (!std::cin) {
            loopTest = false;
        }

        else if (inputWord == "forward" || inputWord == "f") {
            PlayerMove moveResult{};
            moveResult = board->movePlayerForward(player);
            if (moveResult == CELL_BLOCKED) {
                std::cout << "\nUnable to move - cell is blocked.\n";
            }
            else if (moveResult == OUTSIDE_BOUNDS) {
                std::cout << "\nUnable to move - outside bounds.\n";
            }
            else if (moveResult == PLAYER_MOVED) {
                std::cout << "\nPlayer moved.\n";
            }


        }

        else if (inputWord == "turn_left" || inputWord == "l") {
            player->turnDirection(TURN_LEFT);
        }
        else if (inputWord == "turn_right" || inputWord == "r") {
            player->turnDirection(TURN_RIGHT);
        }
        else if (inputWord == "quit") {
            std::cout << "\nTotal player moves: " << player->moves << "\n";
            loopTest = false;
        }
        else {
            Helper::printInvalidInput();
        }
    }
}

