using System;

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
                var key = Console.ReadKey();
                game.Move(key.Key.ToMove());
            }
        }

        static void Render(ThreesGame game)
        {
            Console.Clear();
            for (int x = 0; x < 4; x++)
            {
                for (int y = 0; y < 4; y++)
                {
                    Console.Write(game[x, y].ToString().PadLeft(5));
                }
                Console.Write("\n\n");
            }
            Console.WriteLine(game.Next.ToString().PadLeft(5));

            Console.Write(game.Score.ToString().PadLeft(5));
        }
    }
}
