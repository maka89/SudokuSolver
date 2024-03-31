#include "sudokusolver/solver.hpp"

void ex() {

    uint8_t input_board[9][9] =
    {
    { 7, 0, 0, 0, 9, 0, 0, 8, 0 },
    { 0, 3, 0, 0, 6, 0, 0, 0, 4 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },

    { 2, 0, 0, 0, 0, 0, 0, 0, 5 },
    { 8, 0, 0, 0, 2, 6, 4, 0, 0 },
    { 6, 0, 0, 0, 7, 0, 0, 0, 3 },

    { 0, 1, 0, 0, 4, 0, 0, 0, 9 },
    { 0, 0, 0, 2, 0, 5, 0, 0, 0 },
    { 0, 7, 0, 9, 0, 0, 5, 0, 0 }
    };

    Board b;
    b.setBoard(input_board);
    auto t = solve(b);
    std::cout << StringSolution(t) << std::endl;

}

void ex2() {

    Board b;
    b.setBoard("example_board.txt");

    // Pass pointer to RNG. Useful for finding different solutions for sudokus with multiple solutions.
    std::default_random_engine rng((unsigned)time(0));
    auto t = solve(b, &rng);

    printSolution(t, "solution.txt");

}

int main()
{

    ex();
    ex2();

}
