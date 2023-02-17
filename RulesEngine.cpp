#include <iostream>
#include <cassert>
#include <set>
#include "BoardLocation.h"
#include "LinkedList.h"
#include "RulesEngine.h"
#include "Player.h"
#include "TileBag.h"
#include "Tile.h"

RulesEngine::RulesEngine() {}

RulesEngine::RulesEngine(GamesEngine *gamesEngine) {

    this->ge = gamesEngine;
}

bool RulesEngine::isPlayerHasEnoughTiles(LinkedList *playerHand, const Tile *currentTile) const {

    int count = 0;
    bool playerHas = false;

    for (int i = 0; i < playerHand->size(); i++) {

        if (playerHand->get(i)->shape == currentTile->shape && playerHand->get(i)->colour == currentTile->colour) {
            count++;
        }
    }
    if (count >= 1) {
        playerHas = true;
    }
    return playerHas;
}

bool RulesEngine::isMoveAdjacentToOtherTile(const BoardLocation &move) const {

    int y = move.getRow();
    int x = move.getCol();

    bool tileRight = false;
    bool tileLeft = false;
    bool tileTop = false;
    bool tileBottom = false;

    bool flag = false;


    if (x > 0) {

        if (ge->getTileAt(x - 1, y) != nullptr) {


            if (ge->getBoard()[x - 1][y]->colour == move.tile().colour ||
                ge->getBoard()[x - 1][y]->shape == move.tile().shape) {

                tileLeft = true;

            }
        }

    }

    if (ge->getBoard()[x + 1][y] != nullptr) {

        if (ge->getBoard()[x + 1][y]->colour == move.tile().colour ||
            ge->getBoard()[x + 1][y]->shape == move.tile().shape) {

            tileRight = true;

        }


    }

    if (y > 0) {

        if (ge->getBoard()[x][y - 1] != nullptr) {

            if (ge->getBoard()[x][y - 1]->colour == move.tile().colour ||
                ge->getBoard()[x][y - 1]->shape == move.tile().shape) {

                tileBottom = true;

            }
        }

    }

    if (ge->getBoard()[x][y + 1] != nullptr) {

        if (ge->getBoard()[x][y + 1]->colour == move.tile().colour ||
            ge->getBoard()[x][y + 1]->shape == move.tile().shape) {

            tileTop = true;

        }
    }
    
    if(tileBottom || tileTop || tileLeft || tileRight) {
        return true;
    }
    return flag;

}

bool RulesEngine::isGameOver() {
    // Check if the tile bag is empty and no player has any more tiles
    bool isGameOver = false;
    if (allPlayersHaveEmptyHand()) {
        isGameOver = true;
    }
    return isGameOver;
}

void RulesEngine::applyMove(BoardLocation &move, Player *player) {

    std::vector<Tile *> tiles;
    // Iterate through the move and place the tile on the board

    Tile *tile = new Tile(move.getTile());

    ge->placeTile(move.getCol(), move.getRow(), tile);

    ge->getCurrentPlayer()->playTile(tile);

    tiles.push_back(tile);

}

bool RulesEngine::verifyByLine(std::vector<Tile *> line) const {
    bool passed = false;
    // Check all tiles in the line have same colour
    if (isAllSameColor(line)) {
        passed = true;
    // if all tiles do not have the same colour we check their shape
    } else if (isAllSameShape(line)) {
        passed = true;
    } 
    // Line size means a line does not exist and does not need proofing
    if(line.size() == 0) {
        passed = true;
    }
    // Ensures no duplicate values occur in the line
    if(hasSameTile(line)) {
        passed = false;
    }

    return passed;
}

bool RulesEngine::isAllSameColor(std::vector<Tile*>& row) const {
    bool isSame = true;
    if (row.empty()) {
        isSame = true;
    } else{
        // Will compare all values against the first value of the vector
        char colour = row[0]->colour;
        for (const auto& tile : row) {
            if (tile->colour != colour) {
                isSame = false;
            }
        }
    }
    return isSame;
}

bool RulesEngine::isAllSameShape(std::vector<Tile*>& row) const {
    bool isSame = true;
    if (row.empty()) {
        isSame = true;
    } else{
        // Will compare all values against the first value of the vector
        int shape = row[0]->shape;
        for (const auto& tile : row) {
            if (tile->shape != shape) {
                isSame = false;
            }
        }
    }
    return isSame;
}

bool RulesEngine::hasSameTile(std::vector<Tile*>& row) const {
    std::set<std::string> holder;
    bool hasSame = false;
    if (row.empty()) {
        hasSame = false;
    } else{
        int shape = row[0]->shape;
        char colour = row[0]->colour;
        for (const auto& tile : row) {
            // Tile values stored as a string and passed to set, which allows no duplicate values
            std::string temp = std::string(1, tile->colour) + std::to_string(tile->shape);
            holder.insert(temp);
        }
        // Compare set size and row size to determine if duplicate exists
        // As set silently disposes of insert duplicates and stores a pointer in its place
        // We need to check sizes to evaluate whether duplicate is
        if (holder.size() < row.size()) {
            hasSame = true;
        } 
    }
    return hasSame;
}



bool RulesEngine::allPlayersHaveEmptyHand() {

    bool isGameOver = false;
    Player *player1 = ge->getPlayers()[0];
    Player *player2 = ge->getPlayers()[1];
    Player *player3 = ge->getPlayers()[2];
    Player *player4 = ge->getPlayers()[3];
    if (player1->getPlayerHand()->isEmpty() && player2->getPlayerHand()->isEmpty() 
    && player3->getPlayerHand()->isEmpty() && player4->getPlayerHand()->isEmpty()) {
        isGameOver = true;
    }

    return isGameOver;

}

bool RulesEngine::isPlayerHasTile(LinkedList *playerHand, Tile *tile) const {

    Node *curr = playerHand->getHead();

    while (curr != nullptr) {
        if (curr->tile->colour == tile->colour && curr->tile->shape == tile->shape) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

bool RulesEngine::isValidMove(const BoardLocation &location, Player* player) const {

    bool isValid = true;

    int col = location.getRow();
    int row = location.getCol();

    Tile *tile = new Tile(location.getTile().colour, location.getTile().shape);
    //Vectors to store the
    std::vector<Tile *> horizontalLineVM(7), verticalLineVM(7);

    //Boolean values to check the validity of the move
    bool isMoveAdjacentToOtherTilex = true;
    bool isEmptySpot = false;
    bool playerHasTile = false;
    // Checks to see if board location is empty
    if (ge->getBoard()[row][col] == nullptr) {
        isEmptySpot = true;
    }

    //Check if it has adjacent tiles
    if (!isMoveAdjacentToOtherTile(location)) {
        isMoveAdjacentToOtherTilex = false;
    }

    if(isPlayerHasTile(player->getPlayerHand(), tile)) {
        playerHasTile = true;
    }

    //Check vertical and store in vector
    verticalLineVM = hasVertical(location);

    //Check horizontal and store in vector
    horizontalLineVM = hasHorizontal(location);



    //  If there is > 1 in the line - add the current tile to the line so that it can be validated
    if (horizontalLineVM.size() >= 1) { horizontalLineVM.push_back(tile); }

    ///If there is > 1 in the line - add the current tile to the line so that it can be validated
    if (verticalLineVM.size() >= 1) { verticalLineVM.push_back(tile); }

    //Check the validity of the move overall by validating lines and conditions
    if (!verifyByLine(verticalLineVM) || !verifyByLine(horizontalLineVM) || !isMoveAdjacentToOtherTilex || !isEmptySpot || !playerHasTile) {
        isValid = false;
    } else {
        isValid = true;
    }

    // clean up of resources
    if (horizontalLineVM.size() >= 1) {
        for (int i = 0; i < horizontalLineVM.size(); i++)
        {
            delete horizontalLineVM[i];
        }
    } else {
        for (int j = 0; j < verticalLineVM.size(); j++)
        {
            delete verticalLineVM[j];
        }
    }

    return isValid;

}

int RulesEngine::calculateScores(const BoardLocation &location) {
    int score = 0;
    std::vector<Tile *> horizontalLine, verticalLine;

    Tile *tile = new Tile(location.getTile().colour, location.getTile().shape);

    //Check vertical and store in vector
    verticalLine = hasVertical(location);

    //Check horizontal and store in vector
    horizontalLine = hasHorizontal(location);

    //If there is > 1 in the line - add the current tile to only one line
    if (horizontalLine.size() >= 1) { 
        horizontalLine.push_back(tile); 
    } else if (verticalLine.size() >= 1) { 
        verticalLine.push_back(tile); 
    };     

    // Score is then equal to accumalative line sizes
    score = verticalLine.size() + horizontalLine.size();

    //Check for Qwirkle
    if (verticalLine.size() == 6) {
        score += 6;
        std::cout << "QWIRKLE!!!" << std::endl;
    }

    //Check for Qwirkle
    if (horizontalLine.size() == 6) {
        score += 6;
        std::cout << "QWIRKLE!!!" << std::endl;
    }

    // clean up of resources
    if (horizontalLine.size() >= 1) {
        for (int i = 0; i < horizontalLine.size(); i++)
        {
            delete horizontalLine[i];
        }
    } else {
        for (int j = 0; j < verticalLine.size(); j++)
        {
            delete verticalLine[j];
        }
    }

    return score;
};

std::vector<Tile *>  RulesEngine::hasVertical(const BoardLocation &location) const {

    int col = location.getRow();
    int row = location.getCol();

    std::vector<std::vector<Tile *> > board = ge->getBoard();

    // Create a vector to store the vertical line of tiles
    std::vector<Tile *> verticalLine;
    bool stop = false; 
    // Will search upwards of current position
    for (int j = row - 1; j >= 0; j--) {
        if(board[j][col] != nullptr) {
            verticalLine.push_back(new Tile(board[j][col]->colour, board[j][col]->shape));
        } else {
            j = 0;
        }
    }    

    // Will search downwards from current position
    for (int j = row + 1; j < 26; j++) {
        if(board[j][col] != nullptr) {
            verticalLine.push_back(new Tile(board[j][col]->colour, board[j][col]->shape));
        } else {
            j = 26;
        }
    }
    // Return the line of tiles
    return verticalLine;

}

std::vector<Tile *> RulesEngine::hasHorizontal(const BoardLocation &location) const {
    // get the row and column values from the given BoardLocation object
    int col = location.getRow();
    int row = location.getCol();

    std::vector<std::vector<Tile *> > board = ge->getBoard();

    // create an empty vector to store the line of matching tiles
    std::vector<Tile *> horizontalLine;

    // Will search to the left of current tile on board
    for (int j = col - 1; j >= 0; j--) {
        if(board[row][j] != nullptr) {
            horizontalLine.push_back(new Tile(board[row][j]->colour, board[row][j]->shape));
        } else {
            j = 0;
        }

    }
    // Will search to the right of current tile on board
    for (int j = col + 1; j < 26 ; j++) {
        if(board[row][j] != nullptr) {
            horizontalLine.push_back(new Tile(board[row][j]->colour, board[row][j]->shape));
        } else {
            j = 26;
        }
    }

    return horizontalLine;
}
