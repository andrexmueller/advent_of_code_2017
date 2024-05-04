#include <iostream>
#include <queue>

#define MOD 2147483647

typedef unsigned long long ull;


typedef struct generator {
    ull val;
    ull factor;
} generator;


int compare_nums(int a, int b) {
    for (int i = 0; i < 16; i++) {
        if (a % 2 != b % 2) return 0;
        a /= 2;
        b /= 2;
    }
    return 1;
}


int solve_part_1(generator a, generator b) {
    int pairs = 0;
    for (int i = 0; i < 40'000'000; i++){
        a.val = (a.val * a.factor) % MOD;
        b.val = (b.val * b.factor) % MOD;
        pairs += compare_nums(a.val, b.val);
    }
    return pairs;
}


int solve_part_2(generator a, generator b) {
    int comparisons = 0;
    int pairs = 0;
    std::queue<int> judge_a;
    std::queue<int> judge_b;
    for (int i = 0; comparisons <= 5'000'000; i++) {
        a.val = (a.val * a.factor) % MOD;
        b.val = (b.val * b.factor) % MOD;
        if (a.val % 4 == 0){
            judge_a.push(a.val);
            if (!judge_b.empty()) {
                pairs += compare_nums(judge_a.front(), judge_b.front());
                judge_a.pop();
                judge_b.pop();
                comparisons++;
            }
        }
        if (b.val % 8 == 0){
            judge_b.push(b.val);
            if (!judge_a.empty()) {
                pairs += compare_nums(judge_a.front(), judge_b.front());
                judge_a.pop();
                judge_b.pop();
                comparisons++;
            }
        }
    }
    return pairs;
}



int main() {


    generator a = {783, 16807};
    generator b = {325, 48271};

    std::cout << "Solution for part 1: " << solve_part_1(a, b) << std::endl;
    std::cout << "Solution for part 2: " << solve_part_2(a, b) << std::endl;
    


    return 0;
}