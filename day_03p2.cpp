#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;


class Point {
    public:
        int row, col;

    Point(int row, int col) {
        this->row = row;
        this->col = col;
    }
};


int sum_adj_cells(int **grid, int row, int col) {
    int sum = 0;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            sum += grid[row+i][col+j];
    return sum;
}


int move_point(Point& p, int **grid, char d, int target) {
    if (grid[p.row][p.col] > target) return grid[p.row][p.col];
    switch (d)
    {
    case 'U':
        p.row++;
        break;
    case 'L':
        p.col--;
        break;
    case 'D':
        p.row--;
        break;
    case 'R':
        p.col++;
        break;
    default:
        break;
    }
    int sum = sum_adj_cells(grid, p.row, p.col);
    grid[p.row][p.col] = sum;
    return sum;
}




int main() {
    
    int **grid = (int**) malloc(sizeof(int*) * 1024);
    for (int i=0; i<1024; i++) {
        grid[i] = (int*) calloc(1024, sizeof(int));
    }


    int start_row = 512;
    int start_col = 512;

    Point p(start_row, start_col);
    grid[start_row][start_col] = 1;


    int k = 0;
    int sum{};
    int puzzle_input = 312051;
    
    while(sum < puzzle_input) {
        for (int i=0; i < 2*k+1; i++) {
            sum = move_point(p, grid, 'R', puzzle_input);
            
        }
        for (int i=0; i < 2*k+1; i++) {
            sum = move_point(p, grid, 'U', puzzle_input);
            
        }
        for (int i=0; i < 2*k+2; i++) {
            sum = move_point(p, grid, 'L', puzzle_input);
            
        }
        for (int i=0; i < 2*k+2; i++) {
            sum = move_point(p, grid, 'D', puzzle_input);
            
        }
    
        k++;
    }

    cout << "Part 2 solution -> " << sum << endl;
    
    // freeing grid mem
    for (int i=0; i<1024; i++) free(grid[i]);
    free(grid);
    return 0;
}