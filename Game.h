#pragma once
#include <vector>
#include <string>
#include "Player.h"

using namespace std;

class Game
{
public:
	Game(unsigned sizeInput = 3);
	int turnTaken = 0;

protected:


private:
	unsigned GRID_SIZE;
	vector<Player> players;
	vector< vector< string > > grid;
	vector< vector< string > > winningCombinations;

	void setGameType(vector<Player> &players);
	void initializeGrid(vector< vector<string> > &grid);
	void displayGrid(vector< vector<string> > grid);

	//modification: should check for vertices?
	vector< vector< string > > generateCombinations(bool vertices);
	vector<string> singleCombination(int a, int b, int c);

	void clearConsole();
	void pause();
	
	unsigned convertPosition(unsigned row, unsigned column);
	pair<unsigned, unsigned> convertRowCol(string position);

	unsigned takePlayerInput();
	int takeIntInput();
	char takeCharInput();
	char takePlayerSymbol();

	void takeTurn(vector< vector<string> > &grid, Player currentPlayer);
	bool checkState(vector< vector<string> > grid);
	void play(vector< vector<string> > &grid);

	bool AI_Deffensive(vector < vector<string> > &grid, Player AI, int cellsRemaining);
	bool AI_Offensive(vector < vector<string> >& grid, Player AI);
	void AI_random(vector < vector<string> >& grid, Player AI);

	//mods
	bool whoShouldStart(bool current);
	bool checkForVertices();

	void debug(vector<Player> players);
};

