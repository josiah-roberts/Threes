using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using static System.Math;
using static System.Linq.Enumerable;

namespace Threes
{
    class Board
    {
        private Random _rng = new Random();
        private int[,] _matrix;
        
        private Board(int[,] matrix)
        {
            _matrix = matrix;
        }

        private Board()
        {
            _matrix = new int[4, 4];
        }

        public int Score
        {
            get
            {
                int ret = 0;
                for (int x = 0; x < 4; x++)
                    for (int y = 0; y < 4; y++)
                        if (this[x, y] >= 3)
                            ret += (int)Pow(3, Log(this[x, y] / 3, 2) + 1);
                return ret;
            }
        }

        public int this[int x, int y]
        {
            get
            {
                return _matrix[x, y];
            }
        }

        public bool Move(Move move, int NextCard)
        {
            var preparedBoard = _matrix.ForMove(move);
            var shiftedBoard = preparedBoard.ShiftLeft();

            if (shiftedBoard.Cast<int>().SequenceEqual(preparedBoard.Cast<int>()))
                return false;

            var emptyCells = Range(0, 4).Where(x => shiftedBoard[x, 3] == 0).ToList();
            var cell = _rng.Pop(emptyCells);

            shiftedBoard[cell, 3] = NextCard;
            _matrix = shiftedBoard.FromMove(move);
            return true;
        }

        private void Initialize()
        {
            var initOptions = new List<int> { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };
            var availableCells = Range(0, 16).ToList();
            for (int i = 0; i < 9; i++)
            {
                var selection = _rng.Next(availableCells.Count);
                var cell = availableCells[selection];
                availableCells.RemoveAt(selection);
                _matrix[cell % 4, cell / 4] = _rng.Pop(initOptions);
            }
        }

        public static Board StartGame()
        {
            var board = new Board();
            board.Initialize();
            return board;
        }
    }
}
