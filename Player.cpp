#include "Player.h"

using namespace std;

Player::Player(bool type, char playersCharacter) {
	isAi = type;
	symbol = playersCharacter;
}