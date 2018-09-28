#ifndef GAME_CLASS
#define GAME_CLASS

#include <string>
#include <vector>
using namespace std;

class Game
{
  private:
    int board[16];
    vector<int> draw_deck;
    void fill_tile(int start, int step);

  public:
    bool custom_draw = false;
    void record_draw(int position, int value);
    vector<int> next_tiles;
    bool move(string direction);
    bool canMove();
    bool canMove(string move);
    int score();
    void render();
    Game(const int (&board)[16]);    
};

#endif
