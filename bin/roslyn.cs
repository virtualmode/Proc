using System;

namespace ConsoleApp
{
    class Program
    {
        public static int Fibonacci(int n)
        {
            if (n < 2)
                return n;
            else
                return Fibonacci(n - 1) + Fibonacci(n - 2);
        }

        static void Main(string[] args)
        {
            Console.WriteLine($"Hello, Fibonacci! {Fibonacci(8)}");
        }
    }
}
