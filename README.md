# SudokuSolver
Sudoku solver in C++. 

## Language Standard
By default the code uses C++20 language standard features to calculate the timestamp of the solution. 
By defining the preprocessor definition SUDOKU_DISABLE_TIMESTAMP, you can remove this feature. And compile on earlier C++ standards.

## Usage

```c++
  Board b;
  b.setBoard("example_board.txt");

  // Pass pointer to RNG. Useful for finding different solutions for sudokus with multiple solutions.
  std::default_random_engine rng((unsigned)time(0));
  auto t = solve(b, &rng);

  printSolution(t, "solution.txt");
```
See example.cpp
