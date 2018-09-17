using System;
using static System.Console;

namespace Threes
{
    class Program
    {
        static void Main(string[] args)
        {
            var game = new ThreesGame();
            while (true)
            {
                Render(game);
                var key = ReadKey();
                game.Move(key.Key.ToMove());
            }
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
