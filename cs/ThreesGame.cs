using System;
using System.Collections.Generic;
using System.Linq;
using static System.Math;
using static System.Linq.Enumerable;

namespace Threes
{
    class ThreesGame
    {
        private Random _rng = new Random();
        private Board _board = Board.StartGame();
        private int[] _next;
        public int[] Next => _next;

        public ThreesGame()
        {
            AdvanceNext();
        }

        public int this[int x, int y]
        {
            get
            {
                return _board[x, y];
            }
        }

        private List<int> _drawDeck = new List<int>();
        void AdvanceNext()
        {
            var max = _board.Max;
            if (max >= 48 && _rng.Next(20) == 0)
            {
                _next = Range(0, (int)(Log(max / 3) / Log(2)) - 3)
                        .Select(x => 6 * (int)Pow(2, x)).ToArray();
                return;
            }

            if (!_drawDeck.Any())
                _drawDeck = new List<int> { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };

            _next = new[] { _rng.Pop(_drawDeck) };
        }

        public int Score => _board.Score;
        
        public bool Move(Move move)
        {
            if (_board.Move(move, _rng.Pick(Next)))
            {
                AdvanceNext();
                return true;
            }
            return false;
        }
    }
}
