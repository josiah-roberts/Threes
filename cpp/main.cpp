#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include "shifting.h"
#include <vector>
using namespace std;

enum Direction : int {left = 0, right = 1, up = 2, down = 3};

int max_tile(int (&array)[16])
{
    int max = -1;
    for (int i = 0; i < 16; i++) 
    {
        int x = array[i];
        if (x > max)
            max = x;
    }
    return max;
}

int newDeck[] = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
vector<int> draw_deck;

vector<int> next_tiles(int (&array)[16])
{
    int max = max_tile(array);
    if (max >= 48 && rand() % 20 == 0) {

    }
    
    if (draw_deck.empty())
        draw_deck.insert(draw_deck.end(), &newDeck[0], &newDeck[15]);

    int index = rand() % draw_deck.size();
    int item = draw_deck.at(index);
    draw_deck.erase(draw_deck.begin() + index);
    return vector<int>(item, 1);
}

int score(int (&array)[16])
{
    int ret = 0;
    for (int i = 0; i < 16; i++)
        if (array[i] >= 3)
            ret += pow(3, log(array[i] / 3) / log(2) + 1);
    return ret;
}

bool move(int (&array)[16], Direction direction)
{
    switch (direction)
    {
        case Direction::left : return shift_left(array);
        case Direction::right : return shift_right(array);
        case up : return shift_up(array);
        case down : return shift_down(array);
    }
}

bool move(int (&array)[16], string direction)
{
    if (direction == "left")
        return shift_left(array);
    if (direction == "right")
        return shift_right(array);
    if (direction == "up")
        return shift_up(array);
    if (direction == "down")
        return shift_down(array);

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
    int stuff[16] = { 1, 2, 3, 3, 2, 1, 24, 1, 6, 2, 12, 12, 2, 2, 3, 12 };
    render(stuff);

    string last_move;

    do
    {
        getline(cin, last_move);
        move(stuff, last_move);
        render(stuff);

    } while (last_move != "quit");
    
    return 0;
}
