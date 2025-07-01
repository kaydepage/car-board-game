#include "player.h"

Position::Position()
{
    x = 0;
    y = 0;
}


Position::Position(int x, int y)
{
    Position::x = x;
    Position::y = y;
}

Player::Player() : position {Position()}, direction {NORTH}
{
    
}

void Player::initialisePlayer(Position* position, Direction direction)
{
    Player::position = *position;
    Player::direction = direction;
    moves = 0u;
}


void Player::turnDirection(TurnDirection turnDirection) {
    int currentDirection = static_cast<int>(this->direction);
    int turn;
    if (turnDirection) {
        turn = 1;
    }
    else {
        turn = -1;
    }
    int newDirection = abs((currentDirection + turn + 4)) % 4;
    this->direction = static_cast<Direction>(newDirection);
}



Position Player::getNextForwardPosition()
{  
    Position returnPos = Player::position; 
    
    if (this->direction == NORTH) {
        returnPos.y = returnPos.y - 1;
    }
    if (this->direction == EAST) {
        returnPos.x= returnPos.x + 1;
    }
    if (this->direction == SOUTH) {
        returnPos.y = returnPos.y + 1;
    }
    if (this->direction == WEST) {
        returnPos.x = returnPos.x - 1;
    }

    return returnPos;
}

void Player::updatePosition(Position position)
{
    this->position = position;
    moves++;
}

void Player::displayDirection()
{
    if (this->direction == NORTH) {
        std::cout<<DIRECTION_ARROW_OUTPUT_NORTH;
    }
    if (this->direction == EAST) {
        std::cout<<DIRECTION_ARROW_OUTPUT_EAST;
    }
    if (this->direction == SOUTH) {
        std::cout<<DIRECTION_ARROW_OUTPUT_SOUTH;
    }
    if (this->direction == WEST) {
        std::cout<<DIRECTION_ARROW_OUTPUT_WEST;
    }
}
