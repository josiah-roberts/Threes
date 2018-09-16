﻿using System;
using System.Collections.Generic;

namespace Threes
{
    public static class Extensions
    {
        public static Move ToMove(this ConsoleKey key)
        {
            switch (key)
            {
                case ConsoleKey.UpArrow:
                    return Move.Up;
                case ConsoleKey.DownArrow:
                    return Move.Down;
                case ConsoleKey.LeftArrow:
                    return Move.Left;
                case ConsoleKey.RightArrow:
                    return Move.Right;
                default:
                    return 0;
            }
        }

        public static int[,] ForMove(this int[,] source, Move side)
        {
            var size = source.GetLength(0);
            switch (side)
            {
                case Move.Left:
                    return (int[,])source.Clone();
                case Move.Right:
                    return source.Matrix(OneEighty(size));
                case Move.Up:
                    return source.Matrix(CounterClockwise(size));
                case Move.Down:
                    return source.Matrix(Clockwise(size));
            }
            throw new ArgumentException("Invalid Move", nameof(side));
        }

        private static Func<int, int, (int, int)> Clockwise(int size)
        {
            return (row, column) => (column, size - 1 - row);
        }

        private static Func<int, int, (int, int)> CounterClockwise(int size)
        {
            return (row, column) => (size - 1 - column, row);
        }

        private static Func<int, int, (int, int)> OneEighty(int size)
        {
            return (row, column) => (size - 1 - row, size - 1 - column);
        }

        public static int[,] FromMove(this int[,] source, Move side)
        {
            switch (side)
            {
                case Move.Up:
                    return source.ForMove(Move.Down);
                case Move.Down:
                    return source.ForMove(Move.Up);
                default:
                    return source.ForMove(side);
            }
        }

        public static int[,] Matrix(this int[,] source, Func<int, int, (int, int)> transform)
        {
            var size = source.GetLength(0);
            var ret = new int[size, size];

            for (var x = 0; x < size; x++)
                for (var y = 0; y < size; y++)
                {
                    var (targetX, targetY) = transform(x, y);
                    ret[targetX, targetY] = source[x, y];
                }

            return ret;
        }

        public static int[,] ShiftLeft(this int[,] board)
        {
            var ret = (int[,])board.Clone();
            var height = ret.GetLength(0);
            var width = ret.GetLength(1);

            for (var row = 0; row < height; row++)
            for (var column = 1; column < width; column++)
            {
                if (Combine(ret[row, column - 1], ret[row, column], out var result))
                {
                    ret[row, column] = 0;
                    ret[row, column - 1] = result;
                }
                else if (ret[row, column - 1] == 0)
                {
                    ret[row, column - 1] = ret[row, column];
                    ret[row, column] = 0;
                }
            }
            return ret;
        }

        public static T Pop<T>(this Random r, List<T> list)
        {
            var index = r.Next(list.Count);
            var ret = list[index];
            list.RemoveAt(index);
            return ret;
        }

        private static bool Combine(int a, int b, out int result)
        {
            result = a + b;
            return (a == b && a > 2) || (a != b && a + b == 3);
        }
    }
}