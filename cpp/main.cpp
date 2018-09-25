#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
using namespace std;

enum Direction : int {left = 0, right = 1, up = 2, down = 3};

bool combine(int a, int b, int *result)
{
    *result = a + b;
    return (a == b && a > 2) || *result == 3 || (a == 0 ^ b == 0);
}

bool shift_left(int (&array)[16])
{
    bool moved = false;

    for (int row = 0; row < 4; row++)
    for (int column = 1; column < 4; column++)
    {
        int combination;
        int a = array[row * 4 + (column - 1)];
        int b = array[row * 4 + column];

        if (combine(a, b, &combination))
        {
            array[row * 4 + (column - 1)] = combination;
            array[row * 4 + column] = 0;
            moved = true;
        }
    }

    return moved;
}

bool shift_right(int (&array)[16])
{
    bool moved = false;

    for (int row = 0; row < 4; row++)
    for (int column = 2; column >= 0; column--)
    {
        int combination;
        int a = array[row * 4 + (column + 1)];
        int b = array[row * 4 + column];

        if (combine(a, b, &combination))
        {
            array[row * 4 + (column + 1)] = combination;
            array[row * 4 + column] = 0;
            moved = true;
        }
    }

    return moved;
}

bool shift_up(int (&array)[16])
{
    bool moved = false;

    for (int row = 1; row < 4; row++)
    for (int column = 0; column < 4; column++)
    {
        int combination;
        int a = array[(row - 1) * 4 + column];
        int b = array[row * 4 + column];

        if (combine(a, b, &combination))
        {
            array[(row - 1) * 4 + column] = combination;
            array[row * 4 + column] = 0;
            moved = true;
        }
    }

    return moved;
}

bool shift_down(int (&array)[16])
{
    bool moved = false;

    for (int row = 2; row >= 0; row--)
    for (int column = 0; column < 4; column++)
    {
        int combination;
        int a = array[(row + 1) * 4 + column];
        int b = array[row * 4 + column];

        if (combine(a, b, &combination))
        {
            array[(row + 1) * 4 + column] = combination;
            array[row * 4 + column] = 0;
            moved = true;
        }
    }

    return moved;
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
