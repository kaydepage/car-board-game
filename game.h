#ifndef GAME_H
#define GAME_H

#include "helper.h"
#include "board.h"
#include "player.h"

// strings used for input validation
#define COMMAND_LOAD "load"
#define COMMAND_INIT "init"
#define COMMAND_FORWARD "forward"
#define COMMAND_FORWARD_SHORTCUT "f"
#define COMMAND_TURN_LEFT "turn_left"
#define COMMAND_TURN_LEFT_SHORTCUT "l"
#define COMMAND_TURN_RIGHT "turn_right"
#define COMMAND_TURN_RIGHT_SHORTCUT "r"
#define COMMAND_QUIT "quit"
#define COMMAND_GENERATE_RANDOM "generate"

#define DIRECTION_NORTH "north"
#define DIRECTION_EAST "east"
#define DIRECTION_SOUTH "south"
#define DIRECTION_WEST "west"

class Game
{
private:

    Board* board;
    Player* player;


    /**
     * Load the board. 
     * Return true if the board is loaded and false for quiting the game.
     */
    bool loadBoard();
    
    /**
     * Initialize the player.
     * Contains options from loadBoard() such as load and generate to
     * reconfigure the board.
     * Return true if the player is initilized and false for quiting the game.
     */
    bool initializePlayer();

    /**
     * Play the game and move the player interactively.
     * Recieves input from the player, and checks if it is one of seven options.
     * If it is forward or f, checks are made to see if the player can move 
     * forward from their current posiiton.
     * 
     * turning options will rotate the player arrow depending if it was l or r.
     * Quitting will bring the player back to mainMenu() as well as displaying the
     * final score of the player for that game.
     */
    void play();


public:

    // initialize and destroy the member variables
    Game();
    ~Game();

    /**
     * Main menu option 1 - play the game as per the specification.
     *
     * This method should call other methods in this class in the following order:
     * - loadBoard()
     * - initilizePlayer()
     * - play() 
     * 
     * These methods should in turn make all the calls to methods in board & player 
     * objects and handle interaction with the user (reading inputs from the console,
     * error checking, etc...).
     */
    void start();
};


#endif
