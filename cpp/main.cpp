#include <iostream>
#include <iomanip>
#include <string>
#include "shifting.h"
#include "drawing.h"
#include <vector>
#include "game.h"
#include <sstream>
#include <array>
using namespace std;

array<string, 4> moves = {"left", "right", "up", "down"};

int play_to_end(Game &game)
{
    int moveCount = 0;
    while (++moveCount < 20 && game.canMove())
    {
        game.move(moves[rand() % 4]);
    }
    return game.score();
}

string find_best_move(Game &game)
{
    string max_move;
    int max_score = 0;

    for (int i = 0; i < moves.size(); i++) {
        string choice = moves[i];
        if (!game.canMove(choice))
            continue;

        int totalScore = 0;
        for (int iteration = 0; iteration < 1000; iteration++)
        {
            Game copy = game;
            copy.custom_draw = false;
            copy.move(choice);
            totalScore += play_to_end(copy);
        }
        if (totalScore > max_score)
        {
            max_score = totalScore;
            max_move = choice;
        }
    }

    return max_move;
}

int main() 
{
    srand(time(NULL));

    cout << "Please enter the game state:" << endl;

    string consoleIn;
    getline(cin, consoleIn);
    std::stringstream stream(consoleIn);
    int n;
    int initialBoard[16];

    for (int i = 0; i < 16; i++)
    {
        stream >> n;
        initialBoard[i] = n;
    }

    Game game = Game(initialBoard);
//    game.custom_draw = true;
    game.render();

    while (game.canMove())
    {
        string bestMove = find_best_move(game);
        cout << "Best move: " << bestMove << endl;
        game.move(bestMove);
        // cout << "What tile dropped? ";
        // int droppedTile;
        // cin >> droppedTile;
        // cout << endl << "What position? ";
        // int position;
        // cin >> position;

        // if (bestMove == "right")
        //     position = position * 4;
        // if (bestMove == "left")
        //     position = (position * 4) + 3;
        // if (bestMove == "up")
        //     position = position + 12;

        // game.record_draw(position, droppedTile);

        // cout << endl << "All right..." << endl;
        game.render();
    }

    cout << "Game over";
    
    cin >> consoleIn;

    return 0;
}
