#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include "shifting.h"
#include "drawing.h"
#include <vector>
using namespace std;

int score(int (&array)[16])
{
    int ret = 0;
    for (int i = 0; i < 16; i++)
        if (array[i] >= 3)
            ret += pow(3, log(array[i] / 3) / log(2) + 1);
    return ret;
}

vector<int> next_tiles;
void fill_tile(int (&array)[16], int start, int step)
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

    next_tiles = draw(array);
}

bool move(int (&array)[16], string direction)
{
    if (next_tiles.empty())
        next_tiles = draw(array);

    if (direction == "left" && shift_left(array))
    {
        fill_tile(array, 3, 4);
        return true;
    }
    if (direction == "right" && shift_right(array))
    {
        fill_tile(array, 0, 4);
        return true;
    }
    if (direction == "up" && shift_up(array))
    {
        fill_tile(array, 12, 1);
        return true;
    }
    if (direction == "down" && shift_down(array))
    {
        fill_tile(array, 0, 1);
        return true;
    }

    return false;
}

bool render(int (&array)[16])
{
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
            cout << setw(4) << array[(x * 4) + y];
        cout << endl << endl;
    }
    cout << score(array) << " : ";
}

int main() 
{
    int stuff[16] = { 1, 2, 3, 3, 2, 1, 0, 0, 6, 0, 12, 12, 0, 2, 0, 12 };
    render(stuff);

    string last_move;

    do
    {
        getline(cin, last_move);
        move(stuff, last_move);
        render(stuff);
        cout << next_tiles.front();
    } while (last_move != "quit");
    
    return 0;
}
