#include <iostream>
#include <iomanip>
#include <string>
#include "shifting.h"
#include "drawing.h"
#include <vector>
#include "game.h"
using namespace std;

int main() 
{
    srand(time(NULL));
    string moves[] = {"left", "right", "up", "down"};
    Game game;
    game.render();

    int moveCount = 0;

    do
    {
        if (game.move(moves[rand() % 4]))
            ++moveCount;

        game.render();
        cout << game.next_tiles.front() << endl << endl;
    } while (game.canMove());
    
    cout << moveCount;
    string crap;
    getline(cin, crap);
    return 0;
}
