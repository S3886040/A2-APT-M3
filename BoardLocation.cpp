#include <iostream>
#include "Tile.h"
#include "BoardLocation.h"


BoardLocation::BoardLocation(int column, int row) {
    x = row;
    y = column;
    score = 0;
}

BoardLocation::BoardLocation(int column, int row, Tile tile) {
    x = row;
    y = column;
    boardTile = tile;
    score = 0;
}

BoardLocation::BoardLocation(const BoardLocation &other) {
    y = other.y;
    x = other.x;
    boardTile = other.boardTile;
}

void BoardLocation::setScore(int score) {
    this->score = score;
}

int BoardLocation::row() const {
    return x;
}

char BoardLocation::column() const {
    return (char) (y);
}

const Tile BoardLocation::tile() const {
    return boardTile;
}

const Tile BoardLocation::getTile() const {
    return this->boardTile;
}

int BoardLocation::getCol() const {

    return this->x;
}

int BoardLocation::getScore() const {

    return this->score;
}

int BoardLocation::getRow() const {

    return this->y;
}