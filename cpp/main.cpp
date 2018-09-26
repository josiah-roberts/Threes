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
    Game game;
    game.render();

    string last_move;

    do
    {
        getline(cin, last_move);
        game.move(last_move);
        game.render();
        cout << game.next_tiles.front();
    } while (last_move != "quit");
    
    return 0;
}
