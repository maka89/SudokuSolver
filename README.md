# SudokuSolver
Sudoku solver in C++. 

## Language Standard
By default the code uses C++20 language standard features to calculate the timestamp of the solution. 
By defining the preprocessor definition SUDOKU_DISABLE_TIMESTAMP, you can remove this feature. And compile on earlier C++ standards.

## Usage

```c++
  #include "sudokusolver/solver.hpp"

  Board b;
  b.setBoard("example_board.txt");
  auto t = solve(b);
  printSolution(t, "solution.txt");
```
See example.cpp for more examples of usage.
