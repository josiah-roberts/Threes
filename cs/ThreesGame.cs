using System;
using System.Collections.Generic;
using System.Linq;

namespace Threes
{
    class ThreesGame
    {
        private Random _rng = new Random();
        private Board _board = Board.StartGame();
        private int _next;
        public int Next => _next;

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
            if (!_drawDeck.Any())
                _drawDeck = new List<int> { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };

            _next = _rng.Pop(_drawDeck);
        }

        public int Score => _board.Score;
        
        public bool Move(Move move)
        {
            if (_board.Move(move, Next))
            {
                AdvanceNext();
                return true;
            }
            return false;
        }
    }
}
