#include "solver.hpp"
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
           
uint8_t input_board_easy[9][9] =
{
{ 9, 1, 0, 3, 4, 0, 0, 0, 7 },
{ 0, 8, 3, 0, 9, 7, 0, 5, 0 },
{ 4, 2, 7, 0, 0, 0, 0, 1, 0 },

{ 0, 0, 2, 6, 8, 0, 4, 0, 0 },
{ 7, 0, 4, 2, 0, 9, 0, 0, 0 },
{ 0, 0, 8, 0, 3, 4, 1, 6, 0 },

{ 8, 0, 0, 0, 0, 0, 0, 4, 0 },
{ 0, 0, 9, 0, 0, 0, 7, 2, 6 },
{ 0, 5, 6, 0, 0, 3, 8, 0, 1 }
};


int main()
{
    Board b0;
    b0.setBoard(input_board);
    b0.scanBoard();
    b0.printNumPosVals();
    b0.printBoard();




    Board b2;
    b2.setBoard(input_board);
    auto t = solve(b2);
    Board b_solved = std::get<0>(t);
    return_code rc = std::get<1>(t);
    b_solved.printBoard();
    std::cout << rc << std::endl;

}