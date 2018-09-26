#include "shifting.h"

bool can_combine(int a, int b)
{
    return (a == b && a > 2) || a + b == 3 || (a == 0 ^ b == 0);
}

bool combine(int a, int b, int *result)
{
    *result = a + b;
    return can_combine(a, b);
}

bool shift(int (&array)[16], int sourceCell, int targetCell)
{
    int combination;
    int a = array[sourceCell];
    int b = array[targetCell];

    if (combine(a, b, &combination))
    {
        array[targetCell] = combination;
        array[sourceCell] = 0;
        return true;
    }

    return false;
}

bool can_shift_left(int (&array)[16])
{
    for (int row = 0; row < 4; row++)
    for (int column = 1; column < 4; column++)
    if (can_combine(array[row * 4 + column], array[row * 4 + (column - 1)]))
        return true;

    return false;
}

bool can_shift_right(int (&array)[16])
{
    for (int row = 0; row < 4; row++)
    for (int column = 2; column >= 0; column--)
    if (can_combine(array[row * 4 + column], array[row * 4 + (column + 1)]))
        return true;

    return false;
}

bool can_shift_up(int (&array)[16])
{
    for (int row = 1; row < 4; row++)
    for (int column = 0; column < 4; column++)
    if (can_combine(array[row * 4 + column], array[(row - 1) * 4 + column]))
        return true;
            
    return false;
}

bool can_shift_down(int (&array)[16])
{
    bool moved = false;

    for (int row = 2; row >= 0; row--)
    for (int column = 0; column < 4; column++)
    if (can_combine(array[row * 4 + column], array[(row + 1) * 4 + column]))
        return true;

    return false;
}

bool shift_left(int (&array)[16])
{
    bool moved = false;

    for (int row = 0; row < 4; row++)
    for (int column = 1; column < 4; column++)
    if (shift(array, row * 4 + column, row * 4 + (column - 1)))
        moved = true;

    return moved;
}

bool shift_right(int (&array)[16])
{
    bool moved = false;

    for (int row = 0; row < 4; row++)
    for (int column = 2; column >= 0; column--)
    if (shift(array, row * 4 + column, row * 4 + (column + 1)))
        moved = true;

    return moved;
}

bool shift_up(int (&array)[16])
{
    bool moved = false;

    for (int row = 1; row < 4; row++)
    for (int column = 0; column < 4; column++)
    if (shift(array, row * 4 + column, (row - 1) * 4 + column))
        moved = true;

    return moved;
}

bool shift_down(int (&array)[16])
{
    bool moved = false;

    for (int row = 2; row >= 0; row--)
    for (int column = 0; column < 4; column++)
    if (shift(array, row * 4 + column, (row + 1) * 4 + column))
        moved = true;

    return moved;
}
