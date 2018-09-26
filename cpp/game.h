#ifndef GAME_CLASS
#define GAME_CLASS

#include <string>
#include <vector>
using namespace std;

class Game
{
  private:
    int board[16] = {1, 2, 3, 3, 2, 1, 0, 0, 6, 0, 12, 12, 0, 2, 0, 12};
    vector<int> draw_deck;
    void fill_tile(int (&array)[16], int start, int step);

  public:
    vector<int> next_tiles;
    bool move(string direction);
    int score();
    void render();
};

#endif
