using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleCS
{
    class Point
    {
        private int _x;
        private int _y;

        public Point(int x, int y)
        {
            _x = x;
            _y = y;
        }

        public int X
        {
            get
            {
                return _x;
            }
            set
            {
                _x = value;
            }
        }

        public int Y
        {
            get
            {
                return _y;
            }
            set
            {
                if (value < 10)
                    throw new Exception("set property error");
                else
                    _y = value;
            }
        }
    }

    class Program
    {
        
        static void Main(string[] args)
        {
            try
            {
                Point p = new Point(2, 3);
                p.Y = 4;
                Console.WriteLine("x={0},y={1}", p.X, p.Y);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
}
