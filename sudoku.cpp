#include "sudoku.h"

Sudoku::Sudoku(std::string file_path) :_file_path(file_path)
{
	parse_sudoku_file();
}

void Sudoku::parse_sudoku_file()
{
	std::fstream sudoku_file;

	sudoku_file.open(_file_path);

	if (sudoku_file.is_open())
	{
		std::string line;
		while (std::getline(sudoku_file, line))
		{
			parse_line(line);
		}
	}
}

void Sudoku::parse_line(std::string line)
{
	std::vector<int> num_line;

	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ') continue;
		num_line.push_back((int)line[i]-'0');
	}
	sudoku.push_back(num_line);
}

void Sudoku::print_sudoku()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << sudoku[i][j] << ' ';
		}

		std::cout << std::endl;
	}
}
std::vector<int> Sudoku::get_col(int col)
{
	std::vector<int> column;
	for (int i = 0; i < 9; i++)
	{
		column.push_back(sudoku.at(i).at(col));
	}
	return column;
}

std::vector<int> Sudoku::get_row(int row)
{
	return sudoku.at(row);
}

std::vector<int> Sudoku::get_grid(int grid)
{
	std::vector<std::vector<int>> bounds{ {3 * (grid / 3), 3 * (grid / 3) + 2}, {3 * (grid % 3), 3 * (grid % 3) + 2 } };
	std::vector<int> return_grid;
	for (int i = bounds[0][0]; i <= bounds[0][1]; i++)
	{
		for (int j = bounds[1][0]; j <= bounds[1][1]; j++)
		{
			return_grid.push_back(sudoku.at(i).at(j));
		}
	}
	return return_grid;
}

int Sudoku::get_grid_no(int row, int col)
{
	return 3 * (row / 3) + (col / 3);
}

std::vector<int> Sudoku::get_missing_no(int r, int c)
{
	std::vector<int> row = get_row(r);
	std::vector<int> col = get_col(c);
	std::vector<int> grid = get_grid(get_grid_no(r, c));
	std::vector<int> missing;
	std::vector<int> all_nums = all_nums_template;
	for (int i = 0; i < 9; i++)
	{
		all_nums[row[i]] = 0;
		all_nums[col[i]] = 0;
		all_nums[grid[i]] = 0;
	}

	for (int i = 0; i <= 9; i++)
	{
		if (all_nums[i] != 0)
		{
			missing.push_back(all_nums[i]);
		}
	}
	
	return missing;
}

bool Sudoku::fill(std::vector<std::vector<int>>& sudoku)
{
	bool filled = false;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
			{
				std::vector<int> missing = get_missing_no(i, j);
				if (missing.size() == 1)
				{
					sudoku[i][j] = missing[0];
					filled = true;
				}

			}
		}
	}

	return filled;
}

bool Sudoku::is_valid(std::vector<std::vector<int>>& sudoku)
{
	bool valid = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
			{
				std::vector<int> missing = get_missing_no(i, j);
				if (missing.size() == 0)
				{
					valid = false;
				}

			}
		}
	}

	return valid;
}

void Sudoku::recursive_fill(std::vector<std::vector<int>>& sudoku)
{
	bool not_finish = true;
	while (not_finish)
	{
		not_finish = fill(sudoku);
	}
}

bool Sudoku::is_complete(std::vector<std::vector<int>>& sudoku)
{
	bool complete = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
			{
				complete = false;
			}
		}
	}
	return complete;
}

void Sudoku::fill_stack(std::vector<std::vector<int>> sudoku)
{
	if (!is_valid(sudoku))
	{
		return;
	}
	bool break_flag = false;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudoku[i][j] == 0)
			{
				std::vector<int> missing = get_missing_no(i, j);
				break_flag = true;
				for (int k = 0; k < missing.size(); k++)
				{
					std::vector<std::vector<int>> new_sudoku = sudoku;
					new_sudoku[i][j] = missing[k];
					sudoku_stack.push(new_sudoku);
				}
			}
		}
		if (break_flag)
		{
			break;
		}
	}
}

void Sudoku::solve()
{
	std::vector<std::vector<int>> temp_sudoku = sudoku;
	sudoku_stack.push(temp_sudoku);
	while (!is_complete(sudoku) && !sudoku_stack.empty())
	{
		sudoku = sudoku_stack.top();
		sudoku_stack.pop();
		recursive_fill(sudoku);
		fill_stack(sudoku);
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << sudoku[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}
