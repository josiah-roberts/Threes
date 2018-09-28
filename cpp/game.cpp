#include "shifting.h"
#include "drawing.h"
#include "game.h"
#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;

Game::Game(const int (&array)[16])
{
    memcpy(board, array, 16*sizeof(int));
}

void Game::record_draw(int position, int value)
{
    refill_draw_deck(draw_deck);
    board[position] = value;
}

void Game::fill_tile(int start, int step)
{   
    if (custom_draw)
        return;

    if (next_tiles.empty())
        next_tiles = draw(board, draw_deck);

    int options[4] = {start, start + step, start + step * 2, start + step * 3};
    while (true)
    {
        int choice = rand() % 4;
        if (board[options[choice]] == 0)
        {
            board[options[choice]] = next_tiles.at(rand() % next_tiles.size());
            break;
        }
    }

    next_tiles = draw(board, draw_deck);
}

bool Game::move(string direction)
{
    if (draw_deck.empty())
        refill_draw_deck(draw_deck);

    if (direction == "left" && shift_left(board))
    {
        fill_tile(3, 4);
        return true;
    }
    if (direction == "right" && shift_right(board))
    {
        fill_tile(0, 4);
        return true;
    }
    if (direction == "up" && shift_up(board))
    {
        fill_tile(12, 1);
        return true;
    }
    if (direction == "down" && shift_down(board))
    {
        fill_tile(0, 1);
        return true;
    }

    return false;
}

bool Game::canMove()
{
    return can_shift_left(board) || can_shift_right(board) || can_shift_up(board) || can_shift_down(board);
}

bool Game::canMove(string direction)
{
    if (direction == "left" && can_shift_left(board))
        return true;
    if (direction == "right" && can_shift_right(board))
        return true;
    if (direction == "up" && can_shift_up(board))
        return true;
    if (direction == "down" && can_shift_down(board))
        return true;

    return false;
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
            cout << setw(5) << board[(x * 4) + y];
        cout << endl
             << endl;
    }
    cout << "Current score: " << score() << endl;
}
