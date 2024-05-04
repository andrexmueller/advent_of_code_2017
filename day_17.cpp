#include <iostream>


typedef struct Position {
    int val;
    struct Position* next;
} Position;


typedef struct CBuffer {
    int size;
    int steps;
    Position *pos;
} CBuffer;


CBuffer* init_buffer(int steps) {
    CBuffer *cb = (CBuffer*) malloc(sizeof(CBuffer));
    Position *p = (Position*) malloc(sizeof(Position));
    p->val = 0;
    p->next = p;
    cb->pos = p;
    cb->size = 1;
    cb->steps = steps;
    return cb;
}


void insert(CBuffer* cb) {
    Position *new_p = (Position*) malloc(sizeof(Position));
    new_p->val = cb->pos->val + 1;
    for (int i = 0; i < cb->steps; i++) {
        cb->pos = cb->pos->next;
    }
    new_p->next = cb->pos->next;
    cb->pos->next = new_p;
    cb->pos = new_p;
    cb->size++;
}


void clear_CBuffer(CBuffer* cb) {
    Position *start = cb->pos;
    Position *tmp = NULL;
    while (cb->pos != start) {
        tmp = cb->pos;
        cb->pos = cb->pos->next;
        free(tmp);
    }
    free(start);  
    free(cb);
    cb = NULL;  
}


// helper
void print_cb(CBuffer *cb) {
    Position *p = cb->pos;
    std::cout << std::endl;
    std::cout << "(" << p->val << ")" << " ";
    while (p->next != cb->pos) {
        p = p->next;
        std::cout << p->val << " ";
    }
    std::cout << std::endl;
}


// solutions
void solve_part_1(int step) {
    CBuffer *cb = init_buffer(step);
    for (int i = 0; i < 2017; i++) {
        insert(cb);
    }
    std::cout << "Solution for part 1: " << cb->pos->next->val << "\n";
    clear_CBuffer(cb);    
}


void solve_part_2(int step, int runs) {
    int size = 1;
    int pos = 0;
    int val = 0;
    int pos_one = -1;
    for (int i = 0; i < runs; i++) {
        pos = (pos + step % size) % size + 1;
        val++;
        size++;
        if (pos == 1) {
            pos_one = val;
        }
    }
    std::cout << "Solution for part 2: " << pos_one << std::endl;
}

int main() {

    solve_part_1(359);
    solve_part_2(359, 50'000'000);

    return 0;
}