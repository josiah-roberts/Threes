using System;
using System.Collections.Generic;
using static System.Console;

namespace Threes
{
    class Program
    {
        static void Main(string[] args)
        {
            var rng = new Random();
            var maxGame = new ThreesGame();
            for (int i = 0; i < 100_000; i++)
            {
                var moves = new List<Move> { Move.Down, Move.Up, Move.Left, Move.Right };
                var game = new ThreesGame();
                while (moves.Count > 0)
                {
                    //Render(game);
                    var move = rng.Pick(moves);
                    if (!game.Move(move))
                        moves.Remove(move);
                    else
                        moves = new List<Move> { Move.Down, Move.Up, Move.Left, Move.Right };
                }
                
                if (maxGame.Score < game.Score)
                    maxGame = game;
            }
            
            Render(maxGame);

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

            WriteLine("Next");
            Write(new String(' ', 4));

            foreach(var next in game.Next)
                Write(next.ToString().PadRight(4));

            WriteLine("\nScore");
            Write(game.Score.ToString().PadLeft(5));

            WriteLine("\nMove #");
            Write(game.Moves);
        }
    }
}
