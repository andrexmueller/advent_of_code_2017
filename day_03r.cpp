/*

R 1 3 5 7   (0,1)
U 1 3 5 7   (1,0)
L 2 4 6 8   (
D 2 4 6 8


*/

#include <iostream>
#include <cmath>

using namespace std;

class Point {
public:

    int row;
    int col;
    int n = 1;
    int target = 1;

    Point(int row, int col) {
        this->row = row;
        this->col = col;
    }

    void p_move(char d, int steps=1) {
        if (this->n == this->target) return;
        
        steps = this->n + steps > this->target ? this->target - this->n : steps;
        
        if (d == 'U') this->row += steps;
        if (d == 'D') this->row -= steps;
        if (d == 'L') this->col -= steps;
        if (d == 'R') this->col += steps;
        
        this->n += steps;
    }

    void move_to_target() {
        int i = 0;
        while(this->n != this->target) {
            this->p_move('R', 2*i+1);
            this->p_move('U', 2*i+1);
            this->p_move('L', 2*i+2);
            this->p_move('D', 2*i+2);
            i++;
        }
    }
    
    void set_target(int target) { this->target = target; }
    
    int distance_from_origem() {
        return abs(row) + abs(col);
    }

    void print() {
        cout << "(row = " << row << ", col = " << col << ") n = " << n << "\n";
    }


};



int main() {

    Point p(0,0);
    p.set_target(312051);
    p.move_to_target();
    p.print();
    cout << p.distance_from_origem() << endl;

    return 0;
}
