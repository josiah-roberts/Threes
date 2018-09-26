#include "shifting.h"
#include "drawing.h"
#include "game.h"
#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

void Game::fill_tile(int (&array)[16], int start, int step)
{
    int options[4] = {start, start + step, start + step * 2, start + step * 3};
    while (true)
    {
        int choice = rand() % 4;
        if (array[options[choice]] == 0)
        {
            array[options[choice]] = next_tiles.at(rand() % next_tiles.size());
            break;
        }
    }

    next_tiles = draw(array, draw_deck);
}

bool Game::move(string direction)
{
    if (next_tiles.empty())
        next_tiles = draw(board, draw_deck);

    if (direction == "left" && shift_left(board))
    {
        fill_tile(board, 3, 4);
        return true;
    }
    if (direction == "right" && shift_right(board))
    {
        fill_tile(board, 0, 4);
        return true;
    }
    if (direction == "up" && shift_up(board))
    {
        fill_tile(board, 12, 1);
        return true;
    }
    if (direction == "down" && shift_down(board))
    {
        fill_tile(board, 0, 1);
        return true;
    }

    return false;
}

bool Game::canMove()
{
    return can_shift_left(board) || can_shift_right(board) || can_shift_up(board) || can_shift_down(board);
}

int Game::score()
{
    int ret = 0;
    for (int i = 0; i < 16; i++)
        if (board[i] >= 3)
            ret += pow(3, log(board[i] / 3) / log(2) + 1);
    return ret;
}

void Game::render()
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
            cout << setw(4) << board[(x * 4) + y];
        cout << endl
             << endl;
    }
    cout << score() << " : ";
}
