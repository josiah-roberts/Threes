using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using static System.Console;

namespace Threes
{
    class Program
    {
        static void Main(string[] args)
        {
            var moves = new List<Move> { Move.Down, Move.Up, Move.Left, Move.Right };

            var tasks = Enumerable.Range(0, 8).Select(x => Task.Run(() =>
            {
                var rng = new Random();
                var maxGame = new ThreesGame();
                for (int i = 0; i < 100_000; i++)
                {
                    var game = new ThreesGame();
                    var movesWithoutScore = 0;
                    while (movesWithoutScore < 5)
                    {
                        //Render(game);
                        var oldScore = game.Score;
                        game.Move(rng.Pick(moves));

                        if (oldScore == game.Score)
                            movesWithoutScore++;
                        else
                            movesWithoutScore = 0;
                    }

                    if (maxGame.Score < game.Score)
                        maxGame = game;
                }
                return maxGame;
            })).ToArray();

            Task.WaitAll(tasks);
            
            Render(tasks.Select(x => x.Result).OrderByDescending(x => x.Score).First());

            ReadKey();
        }

        static void Render(ThreesGame game)
        {
            Clear();
            for (int x = 0; x < 4; x++)
            {
                for (int y = 0; y < 4; y++)
                {
                    Write(game[x, y].ToString().PadLeft(5));
                }
                Write("\n\n");
            }

            Write(new String(' ', 4));

            foreach(var next in game.Next)
                Write(next.ToString().PadRight(4));

            WriteLine();
            Write(game.Score.ToString().PadLeft(5));
        }
    }
}
