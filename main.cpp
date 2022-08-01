#include<iostream>
#include<vector>

#include "sudoku.h"
#include "sudoku.cpp"

int main()
{
	Sudoku sudoku("sudoku.txt");
	sudoku.print_sudoku();
	std::cout << std::endl;
	std::cout << "solution!" << std::endl << std::endl;
	sudoku.solve();

	return 0;
}