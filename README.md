# A2-APT

Assignment 2, Advanced Prog. Tech. RMIT 2023

## Description

This game is implemented using C++ and includes the following classes:

**BoardLocation**
* Represent the location of the tiles on the board.

**LinkedList**
* Implement a linked list data structure to store player hand tiles.

**Player**
* Represent a player in the game, including their score, name, and tile hand.

**TileBag**
* Store the tiles available for the players to draw from.

**GamesEngine**
* Store the state of the game and manage the game loop.

**RulesEngine**
* Verify the validity of the player's moves and apply them to the game state

## Installing & Executing program

To run this game, you need to have a C++ compiler and the standard library.To compile and run this game, follow these steps:

* Clone this repository
* Navigate to the repository directory
* Run the following command to compile the code:
```
g++ -Wall -Werror -std=c++14 -O -o qwirkle TileBag.cpp Tile.cpp BoardLocation.cpp RulesEngine.cpp GamesEngine.cpp LinkedList.cpp  Node.cpp Player.cpp qwirkle.cpp
```
* Alternatively, you can compile using the provided Makefile:
```
make qwirkle

* Run the following command to execute the code:
```
./qwirkle
```

## Gameplay

The game starts with the player who has the first turn. Each turn, a player can either place tiles on the board or draw tiles from the tile bag. 
When placing tiles, the player must follow the rules of Qwirkle, which require that the tiles be placed adjacent to existing tiles on the board 
and match either the color or shape of the adjacent tiles. Points are earned based on the number of tiles placed and the number of lines created. 
The game continues until all tiles have been placed or the tile bag is empty. The player with the highest score at the end of the game wins.

## Testing

There are 11 tests that can be run to test various aspects of the game. Below are explanations of the purpose of each test
as well as commands used to run them.

AITest: 

Runs gameplay with an AI. As the AI's moves are predictable given a certain board state. Results will always be identical.

AItest Command:
./qwirkle < tests/input/AItest.input > tests/actual_outputs/AItest.gameout

Multi player test: 

Runs gameplay with 3 players. Loads from saved file and feeds input until gameplay has completed.

Multiplayer test command:

./qwirkle < tests/input/Multi_player.input >  tests/actual_outputs/Multi_player.output



## Authors

Contributors names and contact info

 * Philip Hobbs - s3692631@student.rmit.edu.au
 * Justin Healy - s3886040@student.rmit.edu.au
 * Quinn Goh - s3724287@student.rmit.edu.au
 * Braden Cole - s3727913@student.rmit.edu.au

## License

This project is licensed under the MIT License - see the MIT-license.md file for details

## Acknowledgments

