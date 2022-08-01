#pragma once
#include<vector>
#include<stack>
#include<iostream>
#include<string>
#include<fstream>


class Sudoku
{
private:
	// Variables
	std::stack<std::vector<std::vector<int>>> sudoku_stack;
	std::vector<std::vector<int>> sudoku;
	std::vector<int> all_nums_template = { 0,1,2,3,4,5,6,7,8,9 };
	std::string _file_path;
	
	// methods
	void parse_sudoku_file();
	void parse_line(std::string line);
	std::vector<int> get_row(int row);
	std::vector<int> get_col(int col);
	std::vector<int> get_grid(int grid);
	int get_grid_no(int row, int col);
	std::vector<int> get_missing_no(int row, int col);
	bool fill(std::vector<std::vector<int>>& sudoku);
	void recursive_fill(std::vector<std::vector<int>>& sudoku);
	bool is_valid(std::vector<std::vector<int>>& sudoku);
	void fill_stack(std::vector<std::vector<int>> sudoku);
	bool is_complete(std::vector<std::vector<int>>& sudoku);

public:
	Sudoku(std::string file_path);
	void solve();
	void print_sudoku();
};