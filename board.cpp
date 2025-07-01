#include "board.h"

using std::vector;

const vector<vector<Cell>> Board::BOARD_1 =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

Board::Board()
{   
    
    board = new std::vector<std::vector<Cell>> {
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
    };
    //boardSize int added for M4. Is used in place of DEFAULT_BOARD_SIZE and updates based on generation.
    boardSize = 10;
};


Board::~Board()
{
    delete board;
}

void Board::load(int boardId)
{
    resizeBoard(DEFAULT_BOARD_DIMENSION);
    if (boardId == 1) {
        *board = BOARD_1;
    }
    if (boardId == 2) {
        *board = BOARD_2;
    }
}


void Board::resizeBoard(int boardSize)
{
    (*board).assign(boardSize, std::vector<Cell>(boardSize, EMPTY));
    this->boardSize = boardSize;
}

void Board::randomiseBoard(float percentage)
{
    int filledTotal {(int)(percentage * (boardSize * boardSize))};
    std::random_device rd{};
    std::mt19937 mt{rd()};
    std::uniform_int_distribution<> cellRand{0, boardSize - 1};


    while (filledTotal > 0) {
        int row {cellRand(mt)};
        int col {cellRand(mt)};
        if ((*board)[col][row] == EMPTY) {
            (*board)[col][row] = BLOCKED;
        if (percentage == 1.0 && filledTotal == 1) {
            (*board)[col][row] = EMPTY;
        }
            filledTotal--;
        }
        
    }
}

bool Board::generateResult(std::vector<std::string> stringVector)
{   
    bool result{};
    std::string genInput{};
    /**
     * genInput is used to place the whitespace removed strings
     * from stringVector into a single string with no whitespace.
     * 
     * This can then be used by splitString, splitting on commas.
    */
    for (size_t i{1}; i < stringVector.size(); i++) {
        genInput += stringVector[i];
    }

    std::vector<std::string> genString;
    Helper::splitString(genInput, genString, ",");
    /**
     * Checks size of genString is atleast 2 after removing commas.
     * For instance if input was "generate 10,", this is invalid as
     * it does not specify proportion of the board to be filled.
    */
    if (genString.size() < 2) {
        result = false;
    }
    else {
        std::string boardSize = genString[0];
        std::string boardProportion = genString[1];

        if (!(Helper::isNumber(boardSize) && Helper::isNumber(boardProportion))) {
            result = false;
        }
            
        else if (!(std::stof(boardProportion) >= 0 && std::stof(boardProportion) <= 1.0)) {
            result = false;
        }
        
        else {
            resizeBoard(std::stoi(boardSize));
            randomiseBoard(std::stof(boardProportion));
            result = true;
        }  
    }

    return result;
}

bool Board::initResult(Player* player, std::vector<std::string> stringVector)
{   
    bool result{};
    std::string initInput{};
    std::vector<std::string> directions{"north", "east", "south", "west"};
    /**
     * initInput is used to place the whitespace removed strings
     * from stringVector into a single string with no whitespace.
     * 
     * This can then be used by splitString, splitting on commas.
    */
    for (size_t i{1}; i < stringVector.size(); i++) {
        initInput += stringVector[i];
    }

    std::vector<std::string> initString{};
    Helper::splitString(initInput, initString, ",");

    std::string xCoordString = initString[0];
    std::string yCoordString = initString[1];
    std::string directionString = initString[2];
    /**
     * Checks size of genString is atleast 3 after removing commas.
     * For instance if input was "generate 10,", this is invalid as
     * it does not specify proportion of the board to be filled.
    */
    if (initString.size() < 3) {
        Helper::printInvalidInput();
        result = false;
    }

    else if (!(Helper::isNumber(xCoordString) && std::stoi(xCoordString) < boardSize 
    && std::stoi(xCoordString) >= 0)) {
        Helper::printInvalidInput();
        result = false;
    }

    else if (!(Helper::isNumber(yCoordString) && std::stoi(yCoordString) < boardSize 
    && std::stoi(yCoordString) >= 0)) {
        Helper::printInvalidInput();
        result = false;
    }
    
    else {
        /**
         * This section checks whether directionString matches any index of direction.
         * 
         * If it is found matching a direction index, the board is checked to see if 
         * the given cell is blocked. If it is unblocked, the findDirection result is
         * used to create a Direction object to use in initalising the player.
        */
        auto findDirection = std::find(directions.begin(), directions.end(), directionString);

        if (findDirection != directions.end()) {
            Position attemptedPos{Position(std::stoi(xCoordString), std::stoi(yCoordString))};

            if (placePlayer(attemptedPos)) {
                Direction inputDirection = static_cast<Direction> (findDirection - directions.begin());
                player->initialisePlayer(&attemptedPos, inputDirection);
                std::cout << "\n";
                result = true;
            }
            else {
                std::cout << "Unable to place - cell is blocked.\n";
            }
        }
    }
    

    return result;
}

bool Board::placePlayer(Position position)
{
    bool result = true;
    if ((*board)[position.y][position.x] == BLOCKED) {
        result = false;  
    }
    else if (position.y < 0 || position.y >= boardSize) {
        result = false; 
    }
    else if (position.x < 0 || position.x >= boardSize) {
        result = false;  
    }
    else {
        (*board)[position.y][position.x] = PLAYER;
        result = true; 
    }

    return result;
    
}

PlayerMove Board::movePlayerForward(Player* player)
{
    Position nextForwardPos = player->getNextForwardPosition();
    PlayerMove result = PLAYER_MOVED;
    
    if (nextForwardPos.y < 0 || nextForwardPos.y >= boardSize) {
        result = OUTSIDE_BOUNDS;  
    }
    else if (nextForwardPos.x < 0 || nextForwardPos.x >= boardSize) {
        result = OUTSIDE_BOUNDS;  
    }
    else if ((*board)[nextForwardPos.y][nextForwardPos.x] == BLOCKED) {
        result = CELL_BLOCKED;
    }
    else {
        (*board)[player->position.y][player->position.x] = EMPTY;
        (*board)[nextForwardPos.y][nextForwardPos.x] = PLAYER;
        player->updatePosition(nextForwardPos);
        result = PLAYER_MOVED;
    }

    return result;
}


void Board::display(Player* player)
{
    int counter = 0;
    std::cout << "\n| ";
    for (int k = 0; k < boardSize; k++) {
        std::cout << "|" << counter;
        counter++;
        if (counter > 9) {
            counter = 0;
        }
    }
    std::cout << "|\n";

    counter = 0;
    for (int i = 0; i < boardSize; ++i) {
        std::cout << "|" << counter << "|";
        counter++;
        if (counter > 9) {
            counter = 0;
        }
        for (int j = 0; j < boardSize; ++j) {
            if ((*board)[i][j] == PLAYER) {
                player->displayDirection();
                std::cout << LINE_OUTPUT;
            }
            else if ((*board)[i][j] == BLOCKED) {
                std::cout << BLOCKED_OUTPUT << LINE_OUTPUT;
            }
            else {
                std::cout << EMPTY_OUTPUT << LINE_OUTPUT;
            }
            
        }
        std::cout << "\n";
    }
}


