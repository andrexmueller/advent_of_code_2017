/*
Advent of Code - 2017
Day 3: Spiral Memory


Insight for solving problem:


spiral square

37  36  35  34  33  32  31
38  17  16  15  14  13  30 .
39  18   5   4   3  12  29 .
40  19   6   1   2  11  28 .
41  20   7   8   9  10  27
42  21  22  23  24  25  26 ^
43  44  45  46  47  48  49 |

notice that with 1 in the center, the square with side (2n+1) has (2n+1)^2 at
bottom right corner and (2n)^2 + 1 at top left one.
So, if we set the coords of 1 at (0,0), any integer k must be at


*/



#include <iostream>
#include <cmath>
#include <stdlib.h>
#define abs(x) (x)>=0?(x):-(x)


typedef unsigned long long ull;
using namespace std;


ull solve(ull n) {
    if (n == 1) return 0;
    if (n < 8) return n % 2 == 0 ? 1 : 2;
    ull r = floor(sqrt(n));
    if (r * r == n) return r - 1;

    r = r % 2 == 0 ? r - 1 : r;
    ull s = floor((r+1)/2);
    ull c[] = {
        r * r + s,
        r * r + 2 * s,
        r * r + 3 * s,
        r * r + 4 * s,
        r * r + 5 * s,
        r * r + 6 * s,
        r * r + 7 * s,
    };
    ull d = n;


    for (int i = 0; i < 7; i++){
        //cout << c[i] << " ";
        if (n == c[i])
            return s;
        if (n > c[6])
            return s + n - c[6];
        if (abs(c[i] - n) < d)
            d = abs(c[i] - n);
    }

    return s + d;




}


int main() {


    cout << solve(312051) << endl;

    return 0;
}
