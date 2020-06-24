#include <iostream>
#include "Game.h"
#include <sstream> 

using namespace std;


unsigned getSize() {
    string input = "";
    unsigned size = 0;
    while (true) {
        getline(cin, input);
        stringstream sizeStream(input);
        if (sizeStream >> size) {
            break;
        }
    };
    return size;
}


int main()
{   
    cout << "TicTacToe v. 0.9 by Filip Cholewczuk" << endl;
    unsigned size = 0;

    do {
        cout << "Which would you like to play:\n 1 - CLASSIC 3x3\n 2 - CUSTOM NxN\n [1/2]: ";
        size = getSize();

    } while (size < 1 || size > 2);

    if (size == 1) {
    Game game;
    }
    else if (size == 2) {
        do {
            cout << "Set size from 3 to 10 (reasonable limit): ";
            size = getSize();
        } while (size < 3 || size > 10);
        Game gameCustom(size);
    }



}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
