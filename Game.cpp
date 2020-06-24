#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <random>
#include "Player.h"


using namespace std;

Game::Game(unsigned defaultSize) {
	GRID_SIZE = defaultSize;
	vector< vector< string > > grid{ GRID_SIZE, vector< string >(GRID_SIZE) };

	setGameType(players);
	//debug(players);

	initializeGrid(grid);

	winningCombinations = generateCombinations(checkForVertices());

	play(grid);
}

void Game::setGameType(vector<Player> &players) {
	clearConsole();
	unsigned option = 0;
	char playerSymbol = { 0 };

	do {
		cout << " Would you like to play with another player, or computer?\n 1 - Player vs. Player\n 2 - Player vs Computer\n Option [1/2]: ";
		option = takeIntInput();
	} while (option < 1 || option > 2);

	playerSymbol = takePlayerSymbol();
	bool withAi = false;

	if (option == 1)
	{
		withAi = false;
	}
	else if (option == 2) {
		withAi = true;
	}
	if (playerSymbol == 'X') {
		players.push_back(Player(false, 'X'));
		players.push_back(Player(withAi, 'O'));
	}
	else
	{
		players.push_back(Player(false, 'O'));
		players.push_back(Player(withAi, 'X'));
	}

}

bool Game::checkForVertices() {
	char answer{ 0 };

	do {
		cout << "Would you like to play by vertices [Y/N]: ";
		answer = takeCharInput();
	} while (answer != 'Y' && answer != 'N');

	if (answer == 'Y') {
		return true;
	}
	else {
		return false;
	}
}


void Game::initializeGrid(vector< vector<string> > &grid) {
	int firstTile = 1;

	for (unsigned row = 0; row < GRID_SIZE; ++row){
		for (unsigned column = 0; column < GRID_SIZE; ++column) {
			grid[row][column] = to_string(firstTile);
			firstTile++;
		}
	}
}

//generating combinations of winning scenarios
vector< vector< string > > Game::generateCombinations(bool vertices) {
	vector< vector< string > > combinations;

	if (!vertices) {
		for (unsigned row = 0; row + 2 < GRID_SIZE; ++row) {
			//create vertical combinations

			for (unsigned column = 0; column < GRID_SIZE; ++column) {
				int firstPos = convertPosition(row, column);
				int secondPos = convertPosition(row + 1, column);
				int thirdPos = convertPosition(row + 2, column);
				combinations.push_back(singleCombination(firstPos, secondPos, thirdPos));
			}
		}

		for (unsigned column = 0; column + 2 < GRID_SIZE; ++column) {
			//create horizontal combinations

			for (unsigned row = 0; row < GRID_SIZE; ++row) {
				int firstPos = convertPosition(row , column);
				int secondPos = convertPosition(row, column + 1);
				int thirdPos = convertPosition(row, column + 2);
				combinations.push_back(singleCombination(firstPos, secondPos, thirdPos));
			}
		}
	}
	else{
		for (unsigned row = 0; row + 2 < GRID_SIZE; ++row) {
			for (unsigned column = 0; column + 2 < GRID_SIZE; ++column) {
				//create descending diagonal

				int firstPos = convertPosition(row, column);
				int secondPos = convertPosition(row + 1, column + 1);
				int thirdPos = convertPosition(row + 2, column + 2);
				combinations.push_back(singleCombination(firstPos, secondPos, thirdPos));

				//create ascending diagonal
				firstPos = convertPosition(row, column + 2);
				secondPos = convertPosition(row + 1, column + 1);
				thirdPos = convertPosition(row + 2, column);
				combinations.push_back(singleCombination(firstPos, secondPos, thirdPos));
			}
		}
	}
	return combinations;
}

vector<string> Game::singleCombination(int a, int b, int c) {
	vector<string> combination;
	combination.push_back(to_string(a));
	combination.push_back(to_string(b));
	combination.push_back(to_string(c));
	return combination;
}




void Game::displayGrid(vector< vector<string> > grid) {
	cout << " -";
	for (unsigned i = 0; i < GRID_SIZE; ++i) {
		cout << "-----";
	}
	cout << endl;

	for (unsigned i = 0; i < GRID_SIZE; ++i) {
		cout << " |";
		for (unsigned j = 0; j < GRID_SIZE; ++j) {
			cout << grid[i][j] << setw(5 - grid[i][j].length()) <<" |";
		}
		cout << endl;
	}

	cout << " -";
	for (unsigned i = 0; i < GRID_SIZE; ++i) {
		cout << "-----";
	}
	cout << endl;
}

void Game::clearConsole() {
	system("cls");
}

void Game::pause() {
	system("pause");
}


unsigned Game::convertPosition(unsigned row, unsigned column) {
	unsigned position = 0;
	position = row * GRID_SIZE + column + 1;
	return position;
}

pair<unsigned, unsigned> Game::convertRowCol(string position) {
	pair<unsigned, unsigned> coordinates{ 100, 100 };
	int valueExtracted = 0;
	stringstream posStream(position);

	if (posStream >> valueExtracted) {
		valueExtracted--;
		coordinates.first = valueExtracted / GRID_SIZE;
		coordinates.second = valueExtracted % GRID_SIZE;
		return coordinates;
	}
	else {
		return coordinates;
	}
}

//iterates through possible combinations and checks if conditions are fullfiled
bool Game::checkState( vector< vector<string> > grid ) {
	pair<unsigned, unsigned> positionsChecked;
	string previousChecked;

	for (unsigned i = 0; i < winningCombinations.size(); ++i) {
		previousChecked = "first";
		
		for (unsigned j = 0; j < 3; ++j) {
			do {
			positionsChecked = convertRowCol(winningCombinations[i][j]);
			} while (positionsChecked.first >= GRID_SIZE);

			//first iteration check
			if (previousChecked == "first") {
				if (grid[positionsChecked.first][positionsChecked.second] == "X" || /*grid[positionsChecked.first][positionsChecked.second] ==*/ "O" ) {
					previousChecked = grid[positionsChecked.first][positionsChecked.second];
				}
				//first checked wasn't taken yet, move on
				else {
					break;
				}
			} //second checked doesn't match first, move on
			else if (grid[positionsChecked.first][positionsChecked.second] != previousChecked) {
				break;
			}//last checked is same as other two - win
			else if (grid[positionsChecked.first][positionsChecked.second] == previousChecked && j == 2) {
				return true;
			}
		}
	}

	return false;
}

unsigned Game::takePlayerInput() {
	string userInput = ""; unsigned position = 0;
	
	getline(cin, userInput);
	stringstream intStream(userInput);
		
	if (intStream >> position) {
		return position;
	}
	else {
		cout << "Inappropriate input. Select coordinate from 1 to " << GRID_SIZE * GRID_SIZE << "." << endl;
	}

	return position;
}

int Game::takeIntInput() {
	string buffer = "";
	int input = 0;
	while (true) {
		getline(cin, buffer);
		stringstream inputStream(buffer);
		if (inputStream >> input) {
			return input;
		}
	}
}

char Game::takeCharInput() {
	string buffer = "";
	while (true) {
		getline(cin, buffer);
		stringstream inputStream(buffer);
		if (buffer.length() == 1) {
			return buffer[0];
		}
	}
}

char Game::takePlayerSymbol() {
	char symbol = { 0 };

	do {
		cout << "Would you like to play as 'X' or 'O' [X/O]: ";
		symbol = takeCharInput();
	} while (symbol != 'X' && symbol != 'O');
	return symbol;
}


void Game::takeTurn(vector< vector<string> > &grid, Player currentPlayer) {

	if (!currentPlayer.isAi) {
		while (true) {
			cout << "\nWhere to place '" << currentPlayer.symbol << "':";
			unsigned position = takePlayerInput();
			while (position < 1 || position > GRID_SIZE * GRID_SIZE) {
				cout << "Select position from 1 to " << GRID_SIZE * GRID_SIZE << "." << endl;
				cout << "\nWhere to place '" << currentPlayer.symbol << "':";
				position = takePlayerInput();
			}
			pair<int, int> coordinates = convertRowCol(to_string(position));
			if (coordinates.first == 100)//probably a bad time happens when conversion fails. but what the hell
			{
				continue;
			}
			
			if (grid[coordinates.first][coordinates.second] != to_string(position)) {
				cout << "This position is already taken." << endl;
			}
			else {
				grid[coordinates.first][coordinates.second] = currentPlayer.symbol;
				break;
			}
		}
	}
	else { //AI Section
		//1. Niech sprawdzi czy są kombinacje X X _ i zablokuje // AI_Deffensive bool
		//2. Niech znajdzie, czy są _ _ _ otwarte kombinacje które może // AI_Offensive bool
		//3. Wszędzie gdzie są możliwości X _ _ // AI_Offensive bool
		if (AI_Deffensive(grid, currentPlayer, 1)) { ; }
		else if (AI_Offensive(grid, currentPlayer)) { ; }
		else if (AI_Deffensive(grid, currentPlayer, 2)) { ; }
		else {
			AI_random(grid, currentPlayer);
		}
	}
	turnTaken++;
}

bool Game::AI_Deffensive(vector < vector<string> > &grid, Player AI, int cellsRemaining) {
	string opponentsChar = string(1, players[0].symbol);
	string playersChar = string(1, AI.symbol);

	for (unsigned combination = 0; combination < winningCombinations.size(); ++combination) {
		unsigned timesFound = 0;

		for (unsigned element = 0; element < winningCombinations[combination].size(); ++element) {
			pair<unsigned, unsigned> coordinates = convertRowCol(winningCombinations[combination][element]);

			if (grid[coordinates.first][coordinates.second] == opponentsChar) {
				timesFound++;
			}
		}

		if (3 - timesFound == cellsRemaining) {
			for (unsigned element = 0; element < winningCombinations[combination].size(); ++element) {
				pair<unsigned, unsigned> coordinates = convertRowCol(winningCombinations[combination][element]);

				if (grid[coordinates.first][coordinates.second] != opponentsChar && grid[coordinates.first][coordinates.second] != playersChar) {

					grid[coordinates.first][coordinates.second] = string(1, AI.symbol);
					return true;
				}
			}
		}
	}
	
	return false;
}


bool Game::AI_Offensive(vector < vector<string> >& grid, Player AI) {
	string opponentsChar = string(1, players[0].symbol);
	string playersChar = string(1, AI.symbol);
	vector<int> opportunities;

	for (unsigned combination = 0; combination < winningCombinations.size(); ++combination) {
		unsigned timesFound = 0;

		for (unsigned element = 0; element < winningCombinations[combination].size(); ++element) {
			pair<unsigned, unsigned> coordinates = convertRowCol(winningCombinations[combination][element]);

			if (grid[coordinates.first][coordinates.second] == playersChar) {
				timesFound++;
			}
			else if (grid[coordinates.first][coordinates.second] == opponentsChar) {
				timesFound = -1;
				break;
			}
		}
		opportunities.push_back(timesFound);
	}

	int highest = 0;
	for (auto value : opportunities) {
		if (value > highest) {
			highest = value;
		}
	}

	int index;
	vector<int>::iterator max = find(opportunities.begin(), opportunities.end(), highest);
	if (max != opportunities.cend()) {
		index = distance(opportunities.begin(), max);
	}

	for (unsigned element = 0; element < winningCombinations[index].size(); ++element) {
		pair<unsigned, unsigned> coordinates = convertRowCol(winningCombinations[index][element]);

		if (grid[coordinates.first][coordinates.second] != playersChar && grid[coordinates.first][coordinates.second] != opponentsChar) {
			grid[coordinates.first][coordinates.second] = playersChar;
			return true;
		}
	}	

	return false;
}

void Game::AI_random(vector < vector<string> >& grid, Player AI) {

	int row, column;
	do {
		row = rand() % 9;
		column = rand() % 9;
	} while (grid[row][column] == "X" || "O");
	grid[row][column] = AI.symbol;
}

bool Game::whoShouldStart(bool current) {
	char answer{ 0 };
	do {
		cout << "Should player '" << players[current].symbol << "' start [Y/N]:";
		answer = takeCharInput();
	} while (answer != 'Y' && answer != 'N');
	if (answer == 'Y') {
		return false;
	}
	else
	{
		return true;
	}
}


void Game::play(vector< vector<string> >& grid) {
	bool state = false;
	bool currentPlayer = false;

	//mod: who should start
	currentPlayer = whoShouldStart(currentPlayer);

	do {
		clearConsole();
		displayGrid(grid);

		if (!currentPlayer) {
			takeTurn(grid, players[currentPlayer]);
			currentPlayer = true;
		}
		else {
			takeTurn(grid, players[currentPlayer]);
			currentPlayer = false;
		}
		state = checkState(grid);

		//draw 
		if (turnTaken == GRID_SIZE * GRID_SIZE && !state) {
			break;
		}
	} while ( !state );

	clearConsole();
	displayGrid(grid);

	cout << endl;
	if (turnTaken == GRID_SIZE * GRID_SIZE) {
		cout << "It's a draw~!" << endl;
	}
	else if (state) {
		cout << "Winner found! ";
		if (players[!currentPlayer].isAi) {
			cout << " Computer '" << players[!currentPlayer].symbol << "' won!" << endl;
		}
		else {
			cout << " Player '" << players[!currentPlayer].symbol << "' won!" << endl;
		}
	}
}



void Game::debug(vector<Player> players) {

	/*unsigned col, row;
	while (true) {
		cout << "col: ";
		col = takePlayerInput();
		cout << "row: ";
		row = takePlayerInput();
		cout << convertPosition(row, col) << endl;
	}*/

	/*for (unsigned i = 0; i < winningCombinations.size(); ++i) {
		for (unsigned j = 0; j < winningCombinations[i].size(); ++j) {
			cout << winningCombinations[i][j] << " ";
		}
		cout << endl;
	}*/

	for (int i = 0; i < 2; ++i) {
		cout << players.at(i).isAi << players.at(i).symbol << endl;
	}
}