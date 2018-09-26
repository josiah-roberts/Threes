#include <vector>
#include <math.h>
#include <stdlib.h>
using namespace std;

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
vector<int> bonus_draw(int maximum_tile)
{
    auto ret = vector<int>();
    int bonusCount = (log(maximum_tile / 3) / log(2)) - 3;
    for (int i = 0; i < bonusCount; i++)
        ret.insert(ret.end(), 6 * pow(2, i));

    return ret;
}

vector<int> normal_draw(vector<int> &draw_deck)
{
    if (draw_deck.empty())
        draw_deck.insert(draw_deck.end(), newDeck, (int *)(&newDeck + 1) - 1);

    int index = rand() % draw_deck.size();
    int item = draw_deck.at(index);
    draw_deck.erase(draw_deck.begin() + index);
    return vector<int>(1, item);
}

vector<int> draw(int (&array)[16], vector<int> &draw_deck)
{
    int max = max_tile(array);
    if (max >= 48 && rand() % 20 == 0)
        return bonus_draw(max);
    
    return normal_draw(draw_deck);
}